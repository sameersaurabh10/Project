#include <stdio.h>

int main()
{
	char *temp = "08/08/1995";
	int dd,mm,yy;

	sscanf(temp, "%d%*c%d%*c%d", &dd, &mm, &yy);

	printf("data : %d \n", dd);
	printf("data : %d \n", mm);
	printf("data : %d \n", yy);
	return 0;
}
