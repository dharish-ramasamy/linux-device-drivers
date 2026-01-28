/******************************************************************************

Q3). Build Character Driver in which user application will send ‘a’ or ‘A’ character
     and driver will send back character ‘b’ or ‘B’?

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

#define KERNEL_BUFFER 100

MODULE_AUTHOR("DHARISH");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("If user application send ‘a’ or ‘A’ character, then driver will send back character ‘b’ or 'B'");

char Kbuff[KERNEL_BUFFER];

dev_t dev_num;

struct cdev *mydev;

struct class *myclass;

static int driver_open(struct inode *inode, struct file *file);
static ssize_t driver_read(struct file *file, char __user *buf, size_t count, loff_t *ppos);
static ssize_t driver_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos);
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
    printk("Message driver module inserted..\n");
    int res;

    res = alloc_chrdev_region(&dev_num, 0, 1, "msg_driver");

    if(res < 0)
    {
        printk(KERN_ERR"Error in registration..\n");
    }
    else
    {
        mydev = cdev_alloc();
        mydev->ops = &fops;
        res = cdev_add(mydev, dev_num, 1);

        if(res < 0)
        {
            printk(KERN_ERR"Error in file attachment..\n");
        }

        myclass = class_create("myclass1");
        device_create(myclass, NULL, dev_num, NULL, "msg_driver");
    }
    return 0;
}

static int driver_open(struct inode *inode, struct file *file)
{
    printk("Message driver module opened..\n");
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

    res = copy_to_user(buf, Kbuff, bytes);

    if(res < 0)
    {
        printk(KERN_ERR"Error while copying the data to user..\n");
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
    loff_t fops = *ppos;

    if( fops >= KERNEL_BUFFER )
    {
        return 0;
    }

    if( fops + bytes >= KERNEL_BUFFER )
    {
        bytes = KERNEL_BUFFER - fops;
    }

    res = copy_from_user(Kbuff, buf, bytes);

    if(res < 0)
    {
        printk(KERN_ERR"Error while copying data from user..\n");
    }
    else
    {
        printk("(driver_write) Data has been written into kernel space successfully\n");
    }

    if('a' == Kbuff[0])
    {
        Kbuff[0] = 'b';
    }
    else if('A' == Kbuff[0])
    {
        Kbuff[0] = 'B';
    }

    *ppos = fops + bytes;
    return bytes;
}

static int driver_close(struct inode *inode, struct file *file)
{
    printk("Message driver module closed..\n");
    return 0;
}

static void __exit remove_module(void)
{
    printk("Message driver module removed..\n");
    device_destroy(myclass, dev_num);
    class_destroy(myclass);
    unregister_chrdev_region(dev_num, 1);
    cdev_del(mydev);
}

module_init(insert_module);
module_exit(remove_module);
