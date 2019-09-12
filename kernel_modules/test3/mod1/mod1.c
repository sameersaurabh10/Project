#include <linux/module.h>

static int mod1_exp_func(int i)
{
    pr_info("%s:%d the value passed in is %d\n",
            __func__, __LINE__, i);

    return i;
}
EXPORT_SYMBOL(mod1_exp_func); /* export static symbol */

static int __init mod1_init(void)
{
    pr_info("Initializing simple mod\n");
    return 0;
}

static void __exit mod1_exit(void)
{
    pr_info("This module is exiting\n");
}

module_init(mod1_init);
module_exit(mod1_exit);
MODULE_LICENSE("GPL");
