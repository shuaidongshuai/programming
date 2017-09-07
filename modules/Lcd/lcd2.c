#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/fb.h>
#include <linux/init.h>
#include <linux/dma-mapping.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/wait.h>
#include <linux/platform_device.h>
#include <linux/clk.h>

#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/div64.h>
#include <linux/types.h>
#include <asm/mach/map.h>
#include <mach/regs-lcd.h>
#include <mach/regs-gpio.h>
#include <mach/fb.h>

struct lcd_regs{
	unsigned long   lcdcon1;
    unsigned long	lcdcon2;
	unsigned long	lcdcon3;
	unsigned long	lcdcon4;
	unsigned long	lcdcon5;
	unsigned long	lcdsaddr1;
	unsigned long	lcdsaddr2;
	unsigned long	lcdsaddr3;
	unsigned long	redlut;
	unsigned long	greenlut;
	unsigned long	bluelut; 
	unsigned long	reserved[9];
	unsigned long	dithmode;
	unsigned long	tpal;
	unsigned long	lcdintpnd;
	unsigned long	lcdsrcpnd;
	unsigned long	lcdintmsk;
	unsigned long	lpcsel;
};
static volatile struct lcd_regs *lcd_regs_base;

static struct fb_info *fb_x35;

static volatile unsigned long *gpbcon;
static volatile unsigned long *gpbdat;
static volatile unsigned long *gpccon;
static volatile unsigned long *gpdcon;
static volatile unsigned long *gpgcon;

static u32 pseudo_palette[16];

static inline unsigned int chan_to_field(unsigned int chan,
	struct fb_bitfield* bf)
{
	chan &= 0xffff;
	chan >>= 16 - bf->length;
	
	return chan << bf->offset;
}


//设置颜色
static int x35_setcolreg(unsigned int regno, unsigned int red, 
		unsigned int green, unsigned int blue,
		unsigned int transp, struct fb_info *info)
{
	unsigned int val;
	
	if (regno > 16)
		return 1;

	val  = chan_to_field(red,	&info->var.red);
	val |= chan_to_field(green, &info->var.green);
	val |= chan_to_field(blue,	&info->var.blue);
	
	pseudo_palette[regno] = val;
	
	return 0;

}


static struct fb_ops mini_fb_ops = {
	.owner 			= THIS_MODULE,
	.fb_setcolreg 	= x35_setcolreg,
	.fb_fillrect  	= cfb_fillrect,
	.fb_copyarea  	= cfb_copyarea,
	.fb_imageblit   = cfb_imageblit,
};



static int lcd_init(void)
{
	//1)分配一个fb_info
	fb_x35 = framebuffer_alloc(0, NULL);

	//2)填充fb_info结构
	// 1 设置固定参数
	// 2 设置可变参数
	// 3 设置操作函数
	// 4 其他的设置
	strcpy(fb_x35->fix.id, "mylcd");	
	fb_x35->fix.smem_len 		= 240 * 320 * 32 / 8;  // frambuffer的大小

	fb_x35->fix.type 			= FB_TYPE_PACKED_PIXELS;//扫描方式，以像素点扫描 非隔行扫描	
	fb_x35->fix.visual 			= FB_VISUAL_TRUECOLOR; //色阶 真彩色
	fb_x35->fix.line_length 	= 240 * 4;

	fb_x35->var.xres 			= 240;
	fb_x35->var.yres 			= 320;
	fb_x35->var.xres_virtual 	= 240;
	fb_x35->var.yres_virtual 	= 320;
	fb_x35->var.bits_per_pixel 	= 32;  //每个像素点占有的字节数


	//颜色放置的方式，这里是真彩色为 8:8:8,每种颜色占用8位
	fb_x35->var.red.offset 		= 16;
	fb_x35->var.red.length 		= 8;
	fb_x35->var.blue.offset 	= 8;
	fb_x35->var.blue.length 	= 8;
	fb_x35->var.green.offset 	= 0;
	fb_x35->var.green.length 	= 8;
	
	fb_x35->var.activate 		= FB_ACTIVATE_NOW; //设置颜色立即生效

	//设置操作函数
	fb_x35->fbops 				= &mini_fb_ops;

	fb_x35->pseudo_palette 		= pseudo_palette; //调色板
	fb_x35->screen_size 		= 240 * 320 * 32 / 8;  //屏幕尺寸的大小


	//3)设置硬件，驱动lcd
	// 1 设置lcd引脚可用
	// 2 设置lcd控制器寄存器
	// 3 设置其他的
	gpbcon = ioremap(0x56000010, 8);	
	gpbdat = gpbcon+1;
	gpccon 		= 	ioremap(0x5600020, 4);
	gpdcon 		= 	ioremap(0x5600030, 4);	
	gpgcon 		= 	ioremap(0x5600060, 4);

	*gpccon 	= 	0xaaaaaaaa;
	*gpdcon 	= 	0xaaaaaaaa;
	*gpgcon 	|= 	(0x3 << (4 * 2));  //lcd_pwren lcd电源引脚
	
	lcd_regs_base 	= ioremap(0x4d000000, sizeof(struct lcd_regs));
	
	lcd_regs_base->lcdcon1 = (9 << 8) | (3 << 5) | (0xd << 1);
	lcd_regs_base->lcdcon2 = (8 << 24) | (319 << 14) | (4 << 6) | (9 << 0);
	lcd_regs_base->lcdcon3 = (15 << 19) | (239 << 8) | (16 << 0) ;
	lcd_regs_base->lcdcon4 = 5;
	lcd_regs_base->lcdcon5 = (0 << 12) | (0 << 10) | (1<<6) | (0 << 1) | (0 << 0) ;
			//vsync swap set error

	//分配显存，将显存地址告诉framebuffer
	fb_x35->screen_base 		= dma_alloc_writecombine(NULL, fb_x35->fix.smem_len, 
						&(fb_x35->fix.smem_start), GFP_KERNEL);//fb_x35->fix.smem_start = xxx;  /* 显存的物理地址 */
	lcd_regs_base->lcdsaddr1 	= (fb_x35->fix.smem_start >> 1) & (~(3 << 30)); //[31~0]=0b00xx xxxx ... 30误写成20
	lcd_regs_base->lcdsaddr2 	= ((fb_x35->fix.smem_start + fb_x35->fix.smem_len) >> 1) & 0x1fffff;
	lcd_regs_base->lcdsaddr3 	= (0 << 11) | ((240 * 32 / 16) << 0); //行的长度有错


	//启动lcd
	lcd_regs_base->lcdcon1 		|= (1 << 0);
	lcd_regs_base->lcdcon5 		|= (1 << 3);
	/* MINI2440的背光电路也是通过LCD_PWREN来控制的, 不需要单独的背光引脚 */
	
	//4)注册framebuffer
	register_framebuffer(fb_x35);
	
	return 0;
}

static void lcd_exit(void)
{
	//注销framebuffer结构
	//释放分配的frambuffer显存
	//关闭lcd控制器以及电源
	//取消映射地址
	//释放framebuffer结构
	unregister_framebuffer(fb_x35);
	lcd_regs_base->lcdcon1 		&= ~(1 << 0);
	lcd_regs_base->lcdcon5 		&= ~(1 << 3);
	
	dma_free_writecombine(NULL, fb_x35->fix.smem_len, fb_x35->screen_base, fb_x35->fix.smem_start);

	iounmap(lcd_regs_base);
	iounmap(gpccon);
	iounmap(gpdcon);
	iounmap(gpgcon);

	framebuffer_release(fb_x35);
}


module_init(lcd_init);
module_exit(lcd_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("LCL");