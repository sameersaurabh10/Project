#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//#include <sys/types.h>
//nclude <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fp;

	printf("PID : %d\n", getpid());
	getchar();
	fp = open("abc.txt", 0666);	
	if (fp < 0) {
		printf("Failed to open\n");
	}
	printf("File opened successfully\n");
	getchar();
	return 0;
}
	
