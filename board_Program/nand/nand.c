
#define GSTATUS1        (*(volatile unsigned int *)0x560000B0)
#define BUSY            1

#define NAND_SECTOR_SIZE_LP    2048
#define NAND_BLOCK_MASK_LP     (NAND_SECTOR_SIZE_LP - 1)

typedef unsigned int S3C24X0_REG32;//其实没什么用，只为下面结构体好看

/* NAND FLASH (see S3C2440 manual chapter 6, www.100ask.net) */
typedef struct {
    S3C24X0_REG32   NFCONF;
    S3C24X0_REG32   NFCONT;
    S3C24X0_REG32   NFCMD;
    S3C24X0_REG32   NFADDR;
    S3C24X0_REG32   NFDATA;
    S3C24X0_REG32   NFMECCD0;
    S3C24X0_REG32   NFMECCD1;
    S3C24X0_REG32   NFSECCD;
    S3C24X0_REG32   NFSTAT;
    S3C24X0_REG32   NFESTAT0;
    S3C24X0_REG32   NFESTAT1;
    S3C24X0_REG32   NFMECC0;
    S3C24X0_REG32   NFMECC1;
    S3C24X0_REG32   NFSECC;
    S3C24X0_REG32   NFSBLK;
    S3C24X0_REG32   NFEBLK;
} S3C2440_NAND;

//这个结构体可以说非常鸡肋，只是为了以后阅读高难度代码做铺垫
typedef struct {
    void (*nand_reset)(void);
    void (*wait_idle)(void);
    void (*nand_select_chip)(void);
    void (*nand_deselect_chip)(void);
    void (*write_cmd)(int cmd);
    void (*write_addr)(unsigned int addr);
    unsigned char (*read_data)(void);
}t_nand_chip;
//定义s3c2440_nand这个结构体的好处就在于 只需要对整个结构体设置一次寄存器的地址
// 第一个参数CFCONF就是0x4e000000 第二个参数 就 + 4 unsigned int 和 int一样都是4字节 
static S3C2440_NAND * s3c2440nand = (S3C2440_NAND *)0x4e000000;

// 给结构体定义一个变量
static t_nand_chip nand_chip;

//供外部调用的函数 在 head.S 中  调用
void nand_init(void);
void nand_read(unsigned char *buf, unsigned long start_addr, int size);

/* NAND Flash操作的总入口, 它们将调用S3C2410或S3C2440的相应函数 */
static void nand_reset(void);
static void wait_idle(void);
static void nand_select_chip(void);
static void nand_deselect_chip(void);
static void write_cmd(int cmd);
static void write_addr(unsigned int addr);
static unsigned char read_data(void);

/* S3C2440的NAND Flash处理函数 */
static void s3c2440_nand_reset(void);
static void s3c2440_wait_idle(void);
static void s3c2440_nand_select_chip(void);
static void s3c2440_nand_deselect_chip(void);
static void s3c2440_write_cmd(int cmd);
static void s3c2440_write_addr(unsigned int addr);
static unsigned char s3c2440_read_data(void);

/* S3C2440的NAND Flash操作函数 */

/* 复位 */
static void s3c2440_nand_reset(void)
{
    s3c2440_nand_select_chip();
    s3c2440_write_cmd(0xff);  // 复位命令（0xff）
    s3c2440_wait_idle();
    s3c2440_nand_deselect_chip();
}

/* 等待NAND Flash就绪 */
static void s3c2440_wait_idle(void)
{
    volatile unsigned char *p = (volatile unsigned char *)&s3c2440nand->NFSTAT;
    while(!(*p & BUSY));// 看nand 忙不忙  1 就是不忙 可以往下执行 0就是忙 一直循环
}

/* 发出片选信号 */
static void s3c2440_nand_select_chip(void)
{
    s3c2440nand->NFCONT &= ~(1<<1);// 为 0 就是开启片选
}

/* 取消片选信号 */
static void s3c2440_nand_deselect_chip(void)
{
    s3c2440nand->NFCONT |= (1<<1); //为 1 就是关闭片选
}

/* 发出命令 */
// cmd 这个参数就代表了 命令字
static void s3c2440_write_cmd(int cmd)
{
    volatile unsigned char *p = (volatile unsigned char *)&s3c2440nand->NFCMD;
    *p = cmd;
}

/* 发出地址 */
static void s3c2440_write_addr(unsigned int addr)
{
    volatile unsigned char *p = (volatile unsigned char *)&s3c2440nand->NFADDR;

	// nand 有2048个block（11根地址线）  每个block 有 64 page（6根）每个 page 有2k+64 bytes
	// 下面定义的page 就是 页的绝对值 (用11+6根地址线确定出 是哪个block 中的哪一页)
	//记住只需要知道在 哪个块哪个页（叫做页的绝对值） 就可以啦
// NAND flash 是以页为单位读写数据 而以块为单位擦除数据，所以读的时候不需要管这一页中的地址，因为这一页要全部被访问到
// 计算时可以不用管 格外空间（64字节） 因为读取地址根本不会读到那里面去
	int page = addr / NAND_SECTOR_SIZE_LP;// NAND_SECTOR_SIZE_LP就是页的大小
	
	// 确定出哪一块了就开始读地址了
	// mini2440 nand flash 的型号是 K9F2G08U0B  一共有29根地址线
	// 看 nand 的原理图可以知道 需要 5个周期才能读完（每个周期读8位（只有8个IO接口线）也是以字节）
	// 因为是以页为单位读写数据 所以 页内A0--A11地址线不用管他（都要读完），设为0 就好
	// 我们现在是要告诉nand    读的首地址位于哪个 页，页上个哪个地方不用管
	*p =0;			/* Column Address A0~A7 */	
	
	*p =0; 	/* Column Address A8~A11 */// 列（column）地址 就是页内的地址
	
	*p = page & 0xff;			/* Row Address A12~A19 */// 页地址也叫行（Row）地址
	
	*p = (page >> 8) & 0xff;	/* Row Address A20~A27 */
	
	*p = (page >> 16) & 0x1;	/* Row Address A28 只要读这一个地址序列就好 */
}

/* 读取数据 */
static unsigned char s3c2440_read_data(void)
{
	// 从 NFDATA 中直接读取位于该地址中的数据 
    volatile unsigned char *p = (volatile unsigned char *)&s3c2440nand->NFDATA;
    return *p;
}


/* 在第一次使用NAND Flash前，复位一下NAND Flash */
static void nand_reset(void)
{
    nand_chip.nand_reset();
}

static void wait_idle(void)
{
    nand_chip.wait_idle();
}

static void nand_select_chip(void)
{
    int i;
    nand_chip.nand_select_chip();
    for(i=0; i<10; i++);
}

static void nand_deselect_chip(void)
{
    nand_chip.nand_deselect_chip();
}

static void write_cmd(int cmd)
{
    nand_chip.write_cmd(cmd);
}
static void write_addr(unsigned int addr)
{
    nand_chip.write_addr(addr);
}

static unsigned char read_data(void)
{
    return nand_chip.read_data();
}


/* 初始化NAND Flash */
void nand_init(void)
{
#define TACLS   0
#define TWRPH0  3
#define TWRPH1  0

        nand_chip.nand_reset         = s3c2440_nand_reset;
        nand_chip.wait_idle          = s3c2440_wait_idle;
        nand_chip.nand_select_chip   = s3c2440_nand_select_chip;
        nand_chip.nand_deselect_chip = s3c2440_nand_deselect_chip;
        nand_chip.write_cmd          = s3c2440_write_cmd;
        nand_chip.write_addr         = s3c2440_write_addr;
        nand_chip.read_data          = s3c2440_read_data;

		/* 设置时序 */
        s3c2440nand->NFCONF = (TACLS<<12)|(TWRPH0<<8)|(TWRPH1<<4);
        /* 使能NAND Flash控制器, 初始化ECC, 禁止片选 */
        s3c2440nand->NFCONT = (1<<4)|(1<<1)|(1<<0);
    
    /* 复位NAND Flash */
    nand_reset();
}

/* 读函数 */
void nand_read(unsigned char *buf, unsigned long start_addr, int size)
{
    int i, j;
    
    if ((start_addr & NAND_BLOCK_MASK_LP) || (size & NAND_BLOCK_MASK_LP)) {
        return ;    /* 地址或长度不对齐 */
    }
//因为nand的读取最小单位是Page，所以起始地址必须是Page的首地址，长度必须是页的整数倍
    /* 选中芯片 */
    nand_select_chip();

    for(i=start_addr; i < (start_addr + size);) {
      /* 发出READ0命令 */
      write_cmd(0);

      /* Write Address */
      write_addr(i);
	  
	  //这一步很重要 在nand 中有一个叫 plane(存储层)的东西
	  // 据我所知K9F2G08U0B应该中有两个 plane（好像叫做Two-plane copy-back program）双层叶编程
	  // 每个 plane=2048+64 byte页寄存器  每个plane 包括 1024 block
	 // 第一次只能对 一个层操作  第二次就是对剩下的层操作(so 要两个周期才能读写完)
	  write_cmd(0x30);	//0x30就是第二个周期读的 命令字
			
      wait_idle();// 看nand 忙不忙 也就是读完数据没有

	  // 下面就进行copy 
	  // 把 读到 的 地址上的数据  全部拷贝到  buf 所指向的地址上去
	  // 每次只读取一页的数据 2K
	  // 不管是读地址 还是读数据  都是在一页上操作的
      for(j=0; j < NAND_SECTOR_SIZE_LP; j++, i++) {
          *buf = read_data();
          buf++;
      }
	  // 如果没有拷贝完  超过了一页的大小  起始地址也变到了下一个页地址
	  // 继续上面操作   这也就是为什么 i 也要跟着 buf（复制的目的地址）加 1 原因
    }

    /* 取消片选信号 */
    nand_deselect_chip();
    
    return ;
}

