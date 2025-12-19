#include<linux/init.h>
#include<linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DHARISH");
MODULE_DESCRIPTION("Math Module");

int add( int a , int b );
int sub( int a , int b );
int mul( int a , int b );
int divi( int a , int b );
int avg( int a , int b );

static int __init initial(void)
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

static void __exit removed(void)
{
    printk("Math module removed..\n");
}

module_init(initial);
module_exit(removed);

EXPORT_SYMBOL(add);
EXPORT_SYMBOL(sub);
EXPORT_SYMBOL(mul);
EXPORT_SYMBOL(divi);
EXPORT_SYMBOL(avg);
