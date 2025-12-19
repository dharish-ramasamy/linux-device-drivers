#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DHARISH");
MODULE_DESCRIPTION("User Module");

extern int add( int, int );
extern int sub( int, int );
extern int mul( int, int );
extern int divi( int, int );
extern int avg( int, int );

int a, b;

module_param(a, int, S_IRUGO);
module_param(b, int, S_IRUGO);

static int __init initial(void)
{
    printk("Calculete Module inserted..\n");
    printk("ADD : %d\n", add(a,b));
    printk("SUB : %d\n", sub(a,b));
    printk("MUL : %d\n", mul(a,b));
    printk("DIV : %d\n", divi(a,b));
    printk("AVG : %d\n", avg(a,b));
    return 0;
}

static void __exit removed(void)
{
    printk("Calculate Module removed..\n");
}

module_init(initial);
module_exit(removed);
