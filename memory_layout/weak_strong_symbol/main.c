#include <stdio.h>

extern int abc;
extern int xyz;
extern int test();
extern int view();

int main()
{
	printf("Program starts...\n");
	test();
	view();
	printf("value of abc : %d\n", abc);
	abc=4000;
	printf("value of abc : %d\n", abc);
	printf("value of xyz : %d\n", xyz);
	xyz=200;
	printf("value of xyz : %d\n", xyz);
	printf("Program ends...\n");
	return 0;
}
