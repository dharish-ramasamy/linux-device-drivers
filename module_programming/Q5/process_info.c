/*
 *Q5) Write a module that prints the process id in whose context it was invoked and you may also
 *    print any other process related information.
 */

#include<linux/module.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/sched.h>
#include<linux/timekeeping.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dharish");
MODULE_DESCRIPTION("Process info module");

static int __init insert_process_info(void)
{
   struct task_struct *task = current;
   printk(KERN_INFO "Process info module inserted..\n");
   printk(KERN_INFO "PID: %d\n", task -> pid);
   printk(KERN_INFO "PPID: %d\n", task -> parent -> pid);
   printk(KERN_INFO "TGID: %d\n", task -> tgid);
   printk(KERN_INFO "COMMAND: %s\n", task -> comm);
   printk(KERN_INFO "PRIOITY: %d\n", task -> prio);
   return 0;
}

static void __exit remove_process_info(void)
{
   printk(KERN_INFO "Process info module removed...\n");
}

module_init(insert_process_info);
module_exit(remove_process_info);

