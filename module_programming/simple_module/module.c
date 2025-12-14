/* 
 * Simple module which would print “I am in init module…” when
 * module is inserted & “I am in cleanup module…” when module is removed
*/

#include<linux/init.h>
#include<linux/module.h>

static int __init insert(void)
{
    printk("I am in init module...\n");
    return 0;
}

static void __exit removed(void)
{
    printk("I am in cleanup module...\n");
}

module_init(insert);
module_exit(removed);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dharish");
MODULE_DESCRIPTION("Simple Module");
