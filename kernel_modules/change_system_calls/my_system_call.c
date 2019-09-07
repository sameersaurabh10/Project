#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/syscalls.h>
#include <asm/uaccess.h>

/*For the current process structure*/
#include <linux/sched.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");

int uuid = 0;
module_param(uuid, int, 0644);

/*sys_call_table symbol is exported by kernel
 will use this to replace the original open system call*/
extern void *sys_call_table[];

/*Function pointer to hold the original open system call*/
asmlinkage int (*original_call) (const char *, int, int);

/*This is my open call, which will be called instead of open 
 * system call */
asmlinkage
int my_open_call(const char *filename, int flags, int mode)
{
	printk("MY_OPEN_CALL : open is invoked with file : %s\n", filename);
	printk("Current process uid : %d\n", current->pid);

	if( uuid == current->pid) {
		printk("Module running with fake open_system call\n");
		return 0;
	}

	printk("Module running with original open system call\n");
	
	return original_call(filename, flags, mode);
}

/*Module initialization funciton*/
static 
int __init my_init(void)
{
	printk("Executing my_init funciton\n");
	printk("Passed Argument : %d\n", uuid);
	original_call = sys_call_table[__NR_open];
	sys_call_table[__NR_open] = my_open_call;

	return 0;
}

static
void __exit my_exit(void)
{
	printk("Executing my_exit function\n");
	sys_call_table[__NR_open] = original_call;
	printk("Original my_call is replaced with original call");
}

module_init(my_init);
module_exit(my_exit);
