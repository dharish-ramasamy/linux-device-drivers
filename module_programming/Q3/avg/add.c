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

static int __init initial(void)
{
    printk("Add module Inserted..\n");
    return 0;
}

static void __exit end(void)
{
    printk("Add module Removed..\n");
}

module_init(initial);
module_exit(end);

EXPORT_SYMBOL(add);
