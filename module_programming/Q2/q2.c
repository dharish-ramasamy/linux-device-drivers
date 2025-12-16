#include<linux/init.h>
#include<linux/module.h>
#include<linux/moduleparam.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DHARISH");
MODULE_DESCRIPTION("Param Module");

int a, b;

module_param( a, int, S_IRUGO );
module_param( b, int, S_IRUGO );

static int __init initial(void)
{
    printk("Module Inserted...\n");
    printk("SUM : %d\n", a+b);
    return 0;
}

static void __exit end(void)
{
    printk("Module Removed...\n");
}

module_init(initial);
module_exit(end);

