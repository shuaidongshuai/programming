#include <linux/device.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/stat.h>
#include <linux/kobject.h>

MODULE_LICENSE("GPL");


int kset_filter(struct kset *kset, struct kobject *kobj)
{
		printk("Filter: kobj %s.\n",kobj->name);
		return 0;							//如果为0		下面两个函数就不执行
}

const char *kset_name(struct kset *kset, struct kobject *kobj)//给用户空间传  字符串
{
        static char buf[20];
        printk("Name: kobj %s.\n",kobj->name);
        sprintf(buf,"%s","kset_name");
        return buf;
}
 
int kset_uevent(struct kset *kset, struct kobject *kobj,struct kobj_uevent_env *env)//给用户空间传 发生的事件  的类型
{
        int i = 0;
        printk("uevent: kobj %s.\n",kobj->name);

        while( i < env->envp_idx){
                printk("%s.\n",env->envp[i]);
                i++;
        }

        return 0;
}

struct kset_uevent_ops uevent_ops =//用于处理热插拔事件
{
	.filter = kset_filter,
	.name = kset_name,
	.uevent = kset_uevent,
};

struct kset kset_dong1;
struct kset kset_dong2;
int kset_test_init()
{
	printk("kset test init.\n");
	kobject_set_name(&kset_dong1.kobj,"dong1");//在 /sys/ 目录下创建一个子目录 dong1
	kset_dong1.uevent_ops = &uevent_ops;
	kset_register(&kset_dong1);//注册kset

	kobject_set_name(&kset_dong2.kobj,"dong2");//创建一个目录
	kset_dong2.kobj.kset //指明刚刚创建的目录(kobject)  的父目录 kset (kset_dong1)
	= &kset_dong1;
	kset_register(&kset_dong2);
	return 0;
}

void kset_test_exit()
{
        printk("kset test exit.\n");
        kset_unregister(&kset_dong1);
        kset_unregister(&kset_dong2);
}

module_init(kset_test_init);
module_exit(kset_test_exit);


 
