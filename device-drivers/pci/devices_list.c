#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/pci.h>

MODULE_LICENSE("GPL");
//MODULE_LICENSE("Dual BSD/GPL");

//#define CLASSID 0xff00

static void display_pci_devices(void)
{
	printk("Executing display_pci_devices functtion\n");
	return;
}

static int __init hello_init(void)
{
	printk("Executing hello_init function\n");
	display_pci_devices();
	return 0;
}

static void __exit hello_exit(void)
{
	printk("Executing hello_exit function\n");
}

module_init(hello_init);
module_exit(hello_exit);
