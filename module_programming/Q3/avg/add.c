#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DHARISH");
MODULE_DESCRIPTION("Add Module");

int add(int a, int b);

int add(int a, int b)
{
    return a+b;
}

static int __init insert_add_module(void)
{
    printk("Add module Inserted..\n");
    return 0;
}

static void __exit remove_add_module(void)
{
    printk("Add module Removed..\n");
}

module_init(insert_add_module);
module_exit(remove_add_module);

EXPORT_SYMBOL(add);
