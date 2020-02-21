/* 
 * Sample character device program
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/uaccess.h>


//Declaration
#define MAXDEV 2
static struct cdev cdev;
static struct class *sample_class = NULL;
static int dev_major = 0;

static
int sample_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "Inside sample_open function\n");
	return 0;
}

static
int sample_release(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "Inside sample_release function\n");
	return 0;
}

static
ssize_t sample_read(struct file *file, char __user *buf, size_t count, loff_t *offset)
{
	printk(KERN_INFO "Inside sample_read function\n");
	return 0;
}

static
ssize_t sample_write(struct file *file, const char __user *buf, size_t count, loff_t *offset)
{
	printk(KERN_INFO "Inside sample_write function\n");
	return 0;
}

static
long sample_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	printk(KERN_INFO "Inside sample_ioctl function\n");
	return 0;
}

static int sample_uevent(struct device *dev, struct kobj_uevent_env *env)
{
	printk(KERN_INFO "Inside sample_uevent function\n");
	return 0;
}

static const struct file_operations ops = {
	.owner = THIS_MODULE,
	.open = sample_open,
	.read = sample_read,
	.write = sample_write,
	.release = sample_release,
	.unlocked_ioctl = &sample_ioctl
};

#if 0
static char * sample_devnode(struct device *dev, umode_t *mode)
{
	if (!mode)
		return NULL;

	printk(KERN_INFO "Inside sample_devnode function");

	*mode = 0666;
	return NULL;
}
#endif

static
void create_character_device(void)
{
	//Declaration
	int res;
	dev_t devt;

	//1. Allocation and registration char device numbers using alloc_chrdev_region
	res = alloc_chrdev_region(&devt, 0, MAXDEV, "sample");
	if (res < 0) {
		printk (KERN_INFO "Failed to allocate chrdev region.\n");
		return;
	}

	// To get major and minor number, we can use MAJOR and MINOR macro respectively
	printk(KERN_INFO "Major Number : %d ", MAJOR(devt));
	printk(KERN_INFO "Minor Number : %d ", MINOR(devt));
	dev_major = MAJOR(devt);

	//2. Initialize cdev using cdev_init
	cdev_init(&cdev, &ops);

	//3. Add cdev device to system
	cdev_add(&cdev, devt, 1);

	//4. Create class using class_create
	sample_class = class_create (THIS_MODULE, "chardrv");
	sample_class->dev_uevent = sample_uevent;
//	sample_class->devnode = sample_devnode;

	if (!sample_class) {
		printk(KERN_INFO "Failed to create class.\n");
		return;
	}

	//5. Create character device using device_create
	device_create(sample_class, NULL, MKDEV(dev_major, 0), NULL, "sample");
}

static
int __init sample_init(void)
{
	create_character_device();
	printk (KERN_INFO "Initializing sample driver...\n");
	return 0;
}

static
void __exit sample_exit(void)
{
	printk (KERN_INFO "Destroying sample driver...\n");
	cdev_del(&cdev);

	class_unregister(sample_class);
	if (sample_class)
		class_destroy(sample_class);

	unregister_chrdev_region(MKDEV(dev_major, 0), MINORMASK);
}

module_init(sample_init);
module_exit(sample_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sameer Saurabh");
MODULE_DESCRIPTION("This is sample character driver");
