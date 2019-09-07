#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void strlen_test(int *ptr, int num)
{
	printf("%p\n", ptr);
	printf("%p\n", (ptr + num));
	printf("%d\n", *ptr);
	printf("%d\n", *(ptr + num - 1));
}

int main()
{
	int *ptr = NULL;
	int num = 5, i;
	ptr = (int *) malloc(num + 1);
	for ( i = 0; i< num; i++) {
		*(ptr + i) = i+1;
	}
	
	for ( i = 0; i< num; i++) {
		printf("%d ", ptr[i]);
	}
	printf("\n");
	strlen_test(ptr, num);
	return 0;
}
