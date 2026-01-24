/*
 *Q3) Explore EXPORT_SYMBOL() macro and write simple module dependency program in which
 *    avg module is dependent on add module.
 */

#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DHARISH");
MODULE_DESCRIPTION("Average Module");

int a, b;

module_param(a, int, S_IRUGO);
module_param(b, int, S_IRUGO);

extern int add( int , int );

static int __init insert_avg_module(void)
{
    printk("Average Module Inserted...\n");
    printk("Average is %d.\n", (add(a, b)/2));
    return 0;
}

static void __exit remove_avg_module(void)
{
    printk("Average module removed..\n");
}

module_init(insert_avg_module);
module_exit(remove_avg_module);
