#include <stdio.h>
#include <stdlib.h>

int main()
{
	int *ptr = malloc(sizeof(int));
	if (ptr != NULL)
		free(ptr);

	return 0;
}
