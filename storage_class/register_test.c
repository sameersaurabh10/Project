#include <stdio.h>

int main()
{
	int a = 6;
	register int b = 8;

	while(1) {
		a = a + b;
		printf("a : %d\n", a);
	}
	return 0;
}
