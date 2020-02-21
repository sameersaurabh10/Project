#include <stdio.h>
#include <stdlib.h>

int main()
{
	int *ptr = NULL;

	ptr = (int *) malloc(sizeof(int));
	free(++ptr);
	printf("addr : %p\n", (ptr + 1));
//	free(ptr+1);
	return 0;
}
