#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DHARISH");
MODULE_DESCRIPTION("Math Module to perform add, sub, mul, div, and average");

int add( int a , int b );
int sub( int a , int b );
int mul( int a , int b );
int divi( int a , int b );
int avg( int a , int b );

static int __init insert_math_module(void)
{
    printk("Math module Inserted..\n");
    return 0;
}

int add( int a , int b )
{
    return a+b;
}

int sub( int a , int b )
{
    return a-b;
}

int mul( int a , int b )
{
    return a*b;
}

int divi( int a , int b )
{
    return a/b;
}

int avg( int a , int b )
{
    return (a+b)/2;
}

static void __exit remove_math_module(void)
{
    printk("Math module removed..\n");
}

module_init(insert_math_module);
module_exit(remove_math_module);

EXPORT_SYMBOL(add);
EXPORT_SYMBOL(sub);
EXPORT_SYMBOL(mul);
EXPORT_SYMBOL(divi);
EXPORT_SYMBOL(avg);
