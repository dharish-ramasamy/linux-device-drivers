/******************************************************************************************
 * 
 * Q4). Build the Generic Character Driver which can be used for the more Devices
 *      (user applications) of the same.
 *
 *****************************************************************************************/

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/slab.h>

#define DEVICE_NAME "multi_device"
#define BUF_SIZE (100)

MODULE_AUTHOR("Dharish");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Multiple device");

static int devices = 2;   
module_param(devices, int, 0);

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

struct mydev {
    struct cdev cdev;
    char data[BUF_SIZE];
    int index;         
};

static dev_t dev_num;
static struct class *cls;
static struct mydev **dev_arr;

static int __init insert_module(void)
{
    int i;

    alloc_chrdev_region(&dev_num, 0, devices, DEVICE_NAME);

    cls = class_create("myclass");

    dev_arr = kmalloc_array(devices, sizeof(*dev_arr), GFP_KERNEL);

    for (i = 0; i < devices; i++) 
    {
        dev_arr[i] = kzalloc(sizeof(struct mydev), GFP_KERNEL);
        dev_arr[i]->index = i;

        cdev_init(&dev_arr[i]->cdev, &fops);
        cdev_add(&dev_arr[i]->cdev, MKDEV(MAJOR(dev_num), MINOR(dev_num) + i), 1);

        device_create(cls, NULL, MKDEV(MAJOR(dev_num), MINOR(dev_num) + i), NULL, DEVICE_NAME "%d", i);
    }

    printk(KERN_INFO "Multi Device module inserted..\n");
    return 0;
}

static int driver_open(struct inode *inode, struct file *file)
{
    file->private_data = container_of(inode->i_cdev, struct mydev, cdev);
    printk("Multi Device module opened..\n");
    return 0;
}

static ssize_t driver_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
    struct mydev *d = file->private_data;
    int res;
    size_t bytes = count;
    loff_t fpos = *ppos;  

    if (fpos >= BUF_SIZE)
        return 0;

    if (fpos + bytes > BUF_SIZE)
        bytes = BUF_SIZE - fpos;

    res = copy_to_user(buf, d->data + fpos, bytes);

    if (res < 0)
    {
        printk(KERN_ERR "Error copying data to user.\n");
        return -EFAULT;
    }
    else if (res == 0)
    {
        printk(KERN_INFO "(driver_read) Data read successfully.\n");
    }

    *ppos = fpos + bytes;
    return bytes;
}


static ssize_t driver_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    struct mydev *d = file->private_data;
    int res;
    size_t bytes = count;
    loff_t fpos = *ppos;

    if (fpos >= BUF_SIZE)
        return 0;

    if (fpos + bytes > BUF_SIZE)
        bytes = BUF_SIZE - fpos;

    res = copy_from_user(d->data + fpos, buf, bytes);
    d->data[fpos + bytes] = '\0';

    if (res < 0)
    {
        printk(KERN_ERR "Error copying data from user.\n");
        return -EFAULT;
    }
    else
    {
        printk("(driver_write) Data written successfully.\n");
    }

    *ppos = fpos + bytes;
    return bytes;
}

static int driver_close(struct inode *inode, struct file *file)
{
    printk("Multi Device module closed..\n");
    return 0;
}

static void __exit remove_module(void)
{
    int i;

    for (i = 0; i < devices; i++) {
        device_destroy(cls, MKDEV(MAJOR(dev_num), MINOR(dev_num) + i));
        cdev_del(&dev_arr[i]->cdev);
        kfree(dev_arr[i]);
    }

    kfree(dev_arr);
    class_destroy(cls);
    unregister_chrdev_region(dev_num, devices);

    printk(KERN_INFO "Multi Device module removed..\n");
}

module_init(insert_module);
module_exit(remove_module);
