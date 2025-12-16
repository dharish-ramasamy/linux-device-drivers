/* 
 * Q2).
 *
 * Write a simple module which would print “I am in init module…” when
 * module is inserted & “I am in cleanup module…” when module is removed?
*/

#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DHARISH");
MODULE_DESCRIPTION("Simple Module");

static int __init insert_module(void)
{
    printk("I am in init module...\n");
    return 0;
}

static void __exit remove_module(void)
{
    printk("I am in cleanup module...\n");
}

module_init(insert_module);
module_exit(remove_module);
