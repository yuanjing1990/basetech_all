#include<linux/init.h>  //初始换函数
#include<linux/kernel.h>  //内核头文件
#include<linux/module.h>  //模块的头文件
 
MODULE_LICENSE("shaohef  BSD/GPL");
 
static int __init hello_start(void)
{
    printk(KERN_ALERT "Loading hello module...\n");
    printk(KERN_ALERT "Hello world\n");
    return 0;
}
 
static void __exit hello_end(void)
{
    printk(KERN_ALERT "Goodbye Mr.\n");
}
module_init(hello_start);
module_exit(hello_end);
