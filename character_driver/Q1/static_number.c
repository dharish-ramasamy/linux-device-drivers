/******************************************************************************

Q1). Build simple Character Diver in which device is the memory block and using
     static major number assignment?

*******************************************************************************/

#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/vmalloc.h>
#include<linux/fs.h>
#include<linux/major.h>
#include<linux/cdev.h>
#include<asm/uaccess.h>

MODULE_AUTHOR("Dharish");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Static major number assignment");

#define KERNEL_BUFFER  (100)

char Kbuff[KERNEL_BUFFER];

dev_t dev_num;

static int driver_open(struct inode *inode, struct file *file);
static ssize_t driver_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos);
static ssize_t driver_read(struct file *file, char __user *buf, size_t count, loff_t *ppos);
static int driver_close(struct inode *inode, struct file *file);

struct cdev *mycdev;

struct file_operations fops = {
    .open = driver_open,
    .read = driver_read,
    .write = driver_write,
    .release = driver_close,
};

static int __init insert_module(void)
{
    int res;
    printk("Static major number module inserted...\n");
    dev_num = MKDEV(255, 0);
    printk("Char driver major number : %d\nChar driver minor number : %d\n", MAJOR(dev_num), MINOR(dev_num));
    res = register_chrdev_region(dev_num, 1, "static_driver");
    if(res < 0)
    {
        printk(KERN_ERR"Error in registration..\n");
    }
    else
    {
        mycdev = cdev_alloc();
        mycdev->ops = &fops;
        res = cdev_add(mycdev, dev_num, 1);
        if(res < 0)
        {
            printk(KERN_ERR"Attachment failed..\n");   
        }
    }
    return 0;
}

static int driver_open(struct inode *inode, struct file *file)
{
    printk("Static major number module driver opened..\n");
    return 0;
}

static ssize_t driver_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
    int res;
    size_t bytes = count;
    loff_t fpos = *ppos;

    if( fpos >= KERNEL_BUFFER )
    {
        return 0;
    }

    if( fpos + bytes >= KERNEL_BUFFER )
    {
        bytes = KERNEL_BUFFER - fpos;
    }

    res = copy_to_user((void __user*)buf, (char *)Kbuff, bytes);

    if(res < 0)
    {
        printk("Error in copying the data\n");
        return -EFAULT;
    }
    else if(res == 0)
    {
        printk("(driver_read) Data had been read from kernel-space successully\n");
    }

    *ppos = fpos + bytes;
    return bytes;
}

static ssize_t driver_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    int res;
    ssize_t bytes = count;
    loff_t fpos = *ppos;

    if(fpos >= KERNEL_BUFFER)
    {
        return -ENOSPC;
    }
    
    if(fpos + bytes >= KERNEL_BUFFER)
    {
        bytes = KERNEL_BUFFER - fpos;
    }

    res = copy_from_user((char *)Kbuff, (void __user*)buf, bytes);

    if(res < 0)
    {
        printk("Error while copying data\n");
        return -EFAULT;
    }
    else if(res == 0)
    {
        printk("(driver_write) Data has been written into kernel-space successfully\n");
    }

    printk("Data received from user-space : %s", Kbuff);

    *ppos = fpos + bytes;
    return bytes;
}

static int driver_close(struct inode *inode, struct file *file)
{
    printk("Static major number module driver closed..\n");
    return 0;
}

static void __exit remove_module(void)
{
    unregister_chrdev_region(dev_num, 1);
    cdev_del(mycdev);
    printk("Static major number module removed...\n");
}

module_init(insert_module);
module_exit(remove_module);
