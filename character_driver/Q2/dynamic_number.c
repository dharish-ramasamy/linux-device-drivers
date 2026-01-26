/******************************************************************************

Q2). Build simple Character Diver in which device is the memory block and using
     dynamic major number assignment?

*******************************************************************************/

#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/device.h>
#include<linux/vmalloc.h>
#include<linux/fs.h>
#include<linux/major.h>
#include<linux/cdev.h>
#include<asm/uaccess.h>

MODULE_AUTHOR("DHARISH");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Dynamic major number assignment");

#define KERNEL_BUFFER (100)

char Kbuff[KERNEL_BUFFER];

dev_t dev_num;

struct cdev *mydev;

struct class *my_class;


static int driver_open(struct inode *inode, struct file *file);
static ssize_t driver_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos);
static ssize_t driver_read(struct file *file, char __user *buf, size_t count, loff_t *ppos);
static int driver_close(struct inode *inode, struct file *file);

struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = driver_open,
    .read = driver_read,
    .write = driver_write,
    .release = driver_close,
};

static int __init insert_module(void)
{
    printk("Dynamic major number module inserted...\n");

    int res;

    res = alloc_chrdev_region(&dev_num, 0, 1, "dynamic_driver");

    if(res < 0)
    {
        printk(KERN_ERR"Error in registration\n");
    }
    else
    {
        mydev = cdev_alloc();
        mydev->ops = &fops;
        res = cdev_add(mydev, dev_num, 1);

        my_class = class_create("my_class");
        device_create(my_class, NULL, dev_num, NULL, "dynamic_driver");

        if(res < 0)
        {
            printk(KERN_ERR"Error in file attachment\n");
        }
    }
    return 0;
}

static int driver_open(struct inode *inode, struct file *file)
{
    printk("Dynamic major number module driver opened..\n");
    return 0;
}

static ssize_t driver_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
    int res;
    size_t bytes = count;
    loff_t fops = *ppos;

    if( fops >= KERNEL_BUFFER )
    {
        return 0;
    }

    if( fops + bytes >= KERNEL_BUFFER )
    {
        bytes = KERNEL_BUFFER - fops;
    }

    res = copy_to_user((void __user *)buf, (char *)Kbuff, bytes);

    if(res < 0)
    {
        printk(KERN_ERR"Error in copying data\n");
        return -EFAULT;
    }
    else if(res == 0)
    {
        printk("(driver_read) Data has been read from the kernel space successfully\n");
    }
    
    *ppos = fops + bytes;
    return bytes;
}

static ssize_t driver_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    int res;
    size_t bytes = count;
    loff_t fpos = *ppos;

    if( fpos >= KERNEL_BUFFER )
    {
        return -ENOSPC;
    }
    
    if( fpos + bytes >= KERNEL_BUFFER )
    {
        bytes = KERNEL_BUFFER - fpos;
    }

    res = copy_from_user((char *)Kbuff, (void __user *)buf, bytes);

    if( res < 0 )
    {
        printk(KERN_ERR"Error in copying file\n");
        return -EFAULT;
    }
    else
    {
        printk("(driver_write) Data has been written into kernel space successfully\n");
    }

    printk("Data written by user space : %s\n", Kbuff);

    *ppos = fpos + bytes;
    return bytes;
}

static int driver_close(struct inode *inode, struct file *file)
{
    printk("Dynamic major number module driver closed..\n");
    return 0;
}

static void __exit remove_module(void)
{
    printk("Dynamic major number module removed..\n");
    device_destroy(my_class, dev_num);
    class_destroy(my_class);
    unregister_chrdev_region(dev_num, 1);
    cdev_del(mydev);
}

module_init(insert_module);
module_exit(remove_module);
