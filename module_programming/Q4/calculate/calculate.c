/*
 *Q4) Explore EXPORT_SYMBOL() macro and write simple module dependency program in which
 *    one module implements functionality of add, sub, mul, div and avg operations of two integers
 *    and another module calls these functionalities.
 *
 */

#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DHARISH");
MODULE_DESCRIPTION("Calculate Module to perform add, sub, mul, div and average");

extern int add( int, int );
extern int sub( int, int );
extern int mul( int, int );
extern int divi( int, int );
extern int avg( int, int );

int a, b;

module_param(a, int, S_IRUGO);
module_param(b, int, S_IRUGO);

static int __init insert_calculate_module(void)
{
    printk("Calculete Module inserted..\n");
    printk("ADD : %d\n", add(a,b));
    printk("SUB : %d\n", sub(a,b));
    printk("MUL : %d\n", mul(a,b));
    printk("DIV : %d\n", divi(a,b));
    printk("AVG : %d\n", avg(a,b));
    return 0;
}

static void __exit remove_calculate_module(void)
{
    printk("Calculate Module removed..\n");
}

module_init(insert_calculate_module);
module_exit(remove_calculate_module);
