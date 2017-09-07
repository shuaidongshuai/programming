#include<linux/module.h>
#include<linux/init.h>
#include<linux/cdev.h>//用到了cdev这个结构
#include<linux/fs.h>//用到了file_operations 这个结构
#include<linux/uaccess.h>//copy_to_user	copy_from_user	不管是from还是to   第二个参数总是被拷贝的数据，然后放到第一个参数中去	
						//read中的buf 是要保存的数据  write中的buf 是用户给的数据

int mem_open(struct inode *node, struct file *filp)
{
	int num = MINOR(node->i_rdev);//node->i_rdev获取设备号，高12位为主设备号，低20位为次设备号，MINOR(dev_t dev)是从dev_t中提取出次设备号
	
	if(num==0)//MINOR返回值就可以确定是哪个设备、、、例如num==0  我们就设置是dev1这个模拟设备
		filp->private_data = dev1_register;//把数组的基地址保存到 file 这个结构中去
	if(num==1)
		filp->private_data = dev2_register;
	return 0;
}
ssize_t mem_read(struct file *filp, char __user *buf, size_t size, loff_t *ppos)//loff_t 原型就是 Long型  储存了文件读写位置(偏移量)
{
	int *reg_base = filp->private_data;//从 file 这个结构中 获取 在open中 保存的寄存器（数组）地址
	
	//从内核中拷贝数据到应用程序中copy_to_user(void __user *to, const void *from, unsigned long n)
	copy_to_user(buf, reg_base+(*ppos), size);//1拷贝到buf指针指向的内存中，2拷贝的基地址+偏移，3大小
	
	filp->f_pos += size ;//读写指针会变化，指针指到了 PPOS+size这个位置
	return size ;
}
ssize_t mem_write(struct file *filp, const char __user *buf, size_t size, loff_t *ppos)
{
	int *reg_base = filp->private_data;//从 file 这个结构中 获取 在open中 保存的寄存器（数组）地址
	//从应用程序中拷贝数据到内核中
	copy_from_user(reg_base+(*ppos),buf , size);//unsigned long copy_from_user(void *to, const void __user *from, unsigned long n)
	
	filp->f_pos += size ;//读写指针会变化，指针指到了 PPOS+size这个位置
	return size ;
}
loff_t mem_lseek(struct file *filp, loff_t offset, int whence)//whence来源(取名而已不重要)	offset 代表偏移
{
	loff_t new_pos = 0;//用来储存新的指针位置
		switch (whence){
			case SEEK_SET:new_pos = 0 + offset;break;		//从文件开头
			case SEEK_CUR:new_pos = filp->f_pos + offset;break;	//从当前位置（保存在filp->f_pos中的）
			case SEEK_END:new_pos = 5 * sizeof(int) + offset;break;//从文件尾部
		}
		filp->f_pos = new_pos;//把新指针位置放在 filp->f_pos中去
		return new_pos;//返回值是当前位置
}
int mem_close(struct inode *node, struct file *filp)
{
	return 0;
}

//这个结构体一定要放在这，如果放在最上面会出现 undifined 未定义 原因是上面才创建出mem_lseek	  mem_read这些函数
const struct file_operations memfops =
{
	.llseek = mem_lseek,
	.read = mem_read,
	.write = mem_write,
	.open = mem_open,
	.release = mem_close,
};
//自己的总结：filp->private_data  保存的是基地址 filp->f_pos保存的是当前指针指向的位置

struct cdev mdev;//静态分配cdev
dev_t devnumber;//声明一个可以存放设备号的数  dev_t 实际上就是 unsighted long 型的，，就是起了一个别名而已
//这里模拟两个设备
int dev1_register[5];//用数组来模拟寄存器，这个数组代表了 一个设备的 5 个 寄存器
int dev2_register[5];

int memdev_init()
{
	//初始化cdev
	cdev_init(&mdev, &memfops);//初始化mdev这个cdev结构，fops是设备对应的操作函数集
	
	//动态分配主设备号
	alloc_chrdev_region(&devnumber, 0, 2,"dev_dong");//1存放分配到的主设备号，2起始的次设备号，3分配多少个次设备号，设备名字
	//注册cdev	（添加）设备
	cdev_add(&mdev, devnumber, 2);//1待添加到内核的字符设备结构，2主设备号，3设备个数

	return 0;
}
  
void memdev_exit()
{	
	//设备注销
	cdev_del(&mdev);//要注销的设备结构
	unregister_chrdev_region(devnumber,2);//1.注销的设备号，2.注销几个设备
}

module_init(memdev_init);
module_exit(memdev_exit);