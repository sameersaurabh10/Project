#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("Dual BSD/GPL");

extern int export_test_test(int);

static void test_variables(void)
{
	printk("Executiong test_variables function\n");
}

static int __init second_init(void)
{
	int res;
	printk("SECOND_INIT : Executing my_init function\n");
	res = export_test_test(40);
	printk("Return value : %d\n", res);
	test_variables();
	return 0;
}

static void __exit second_exit(void)
{
	printk("SECOND_EXIT : Executing my_exit function\n");
	export_test_test(100);
}

module_init(second_init);
module_exit(second_exit);
