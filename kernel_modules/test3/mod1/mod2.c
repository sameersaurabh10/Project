#include <linux/module.h>

extern int mod1_exp_func(int);

static int __init mod2_init(void)
{
    pr_info("Initializing mod2\n");
    pr_info("Calling exported function in mod1\n");
    mod1_exp_func(3);
    return 0;
}

static void __exit mod2_exit(void)
{
    pr_info("mod2 exiting\n");
}

module_init(mod2_init);
module_exit(mod2_exit);
MODULE_LICENSE("GPL");
