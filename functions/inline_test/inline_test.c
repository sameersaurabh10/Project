#include "header.h"

int getadd(int a, int b)
{
	return getsum(a, b);
}
int main()
{
	int a = 10, b =30;

	int res = getadd(a, b);
	printf("Sum : %d\n", res);
	return 0;
}
