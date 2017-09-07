#include <linux/device.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/stat.h>

MODULE_LICENSE("GPL");

/*对应于kobject的目录下的一个文件,Name成员就是文件名*/
struct attribute test_attr =
{
	.name ="dong_config",
	.mode = S_IRWXUGO,
};

static struct attribute *def_attrs[] = 
{
	&test_attr,
	NULL,//只有一个文件所以这就填 NULL
};

/*当读文件时执行的操作*/
ssize_t	kobj_test_show(struct kobject *kobject, struct attribute *attr,char *buf)
{
	printk("have show\n");
	printk("attrname:%s\n",attr->name);

	 sprintf(buf,"%s\n",attr->name);
     return strlen(attr->name)+2;//为什么要 +2   因为我们除了返回 名字的长度  还要加上 \n
}

/*当写文件时执行的操作*/
ssize_t	kobj_test_store(struct kobject *kobject,struct attribute *attr,const char *buf, size_t count)
{
	printk("have store\n");
	printk("write:%s\n",buf);
	return count;
	
}

void obj_test_release(struct kobject *kobj)
{
	printk("release\n");
}

//kobject对象的操作
struct sysfs_ops obj_test_sysops =
{
	.show = kobj_test_show,
	.store = kobj_test_store,
};

/*定义kobject对象的一些属性及对应的操作*/
struct kobj_type ktype = 
{
	.release 		=	obj_test_release,
	.sysfs_ops		=	&obj_test_sysops,
	.default_attrs	=	def_attrs,
};

struct kobject kobj;//声明kobject对象
static int kobj_test_init()
{
	printk("Kobject test init\n");
	kobject_init_and_add(&kobj,&ktype,NULL,"kobject_test");//初始化kobject对象kobj,并将其注册到linux系统
	
	return 0;
}

static void kobj_test_exit()
{
	printk("Kobject test exit \n");
	kobject_del(&kobj);
}

module_init(kobj_test_init);
module_exit(kobj_test_exit);



