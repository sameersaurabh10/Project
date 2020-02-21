#include <linux/module.h>
#include <linux/init.h>
#include <linux/netlink.h>

MODULE_LICENSE("Dual GPL");

enum {
	TEST_NL_UNSEPC,
	TEST_NL_ECHO,
	__TEST_NL_MAX,
};

#define TEST_EAMPLE_C_MAX  (__TEST_NL_MAX - 1)

struct genl_family nl_test_family ={
	.id = GENL_ID_GENERATE,
	.name = "NL_TEST",
	.hdrsize = 0,
	.version = 1,
	.maxattr = 3,
};

static struct nla_policy nl_test_nla_policy[] = {
	[TEST_EAMPLE_C_MAX] = {.type = NLA_NUL_STRING},
};


static struct genl_ops nl_test_ops = {
	.cmd = TEST_NL_ECHO,
	.flags = 0,
	.policy = nl_test_nla_policy,
	.doit = test_nl_echo,
	dumpit = NULL	
};


static
int __init nl_test_init(void)
{
	printk("NLTEST : Inside nl_test_init function");
	return 0;
}

static
void __exit nl_test_exit(void)
{
	printk("NLTEST : Inside nl_test_exit function");
}


module_init(nl_test_init);
module_exit(nl_test_exit);
