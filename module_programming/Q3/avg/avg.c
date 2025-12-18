#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DHARISH");
MODULE_DESCRIPTION("Average Module");

int a, b;

module_param(a, int, S_IRUGO);
module_param(b, int, S_IRUGO);

extern int add( int , int );

static int __init avg_insert(void)
{
    printk("Average Module Inserted...\n");
    printk("Average is %d.\n", (add(a, b)/2));
    return 0;
}

static void __exit avg_removed(void)
{
    printk("Average module removed..\n");
}

module_init(avg_insert);
module_exit(avg_removed);
