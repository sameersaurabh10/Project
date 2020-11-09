/*
 * Program which implements own malloc and free function and provides following apis
 *
 *	malloc_init()	:	Reserves 2MB of memory
 *	my_malloc(int)	:	Allocates memory in block(1024 size each)
 *	my_free(addr)	:	Free the allocated blocks
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum{
	FREE,
	BUSY
}status;

typedef struct {
	status status;
	int block;
}memory;

#define TOTAL_MEMORY 2*1024*1024 	//2MB 1KB = 1024 * 2*1024
#define KB 1024		//This is the block size will be allocated after every malloc call
#define BLOCK 1024

char *baseaddr = NULL;
char *threashold = NULL;
char *memoryhead = NULL;
memory memorystatus[2 * KB];

bool malloc_init()
{
	int i;

	for (i = 0; i < 2*1024; i++) {
		memorystatus[i].status = FREE;
		memorystatus[i].block = FREE;
	}

	baseaddr = calloc(TOTAL_MEMORY, sizeof(char));
	if (baseaddr == NULL) {
		perror("Memory initialization failed");
		return false;
	}

	memset(baseaddr, 0, TOTAL_MEMORY);
	threashold = baseaddr + TOTAL_MEMORY;
	memoryhead = baseaddr;
	return true;
}

char *my_malloc(int size)
{
	char *temp = NULL;
	int block = 0, i;
	static int index = 0;

	if (size < 0) return NULL;
	if (baseaddr >= threashold)	return NULL;

	while (size > 0) {
		block++;
		size -= BLOCK;
	}

	if ((baseaddr + block * BLOCK) > threashold) return NULL;
	temp = baseaddr;
	
	if (block == 0) { //my_malloc is called with 0 size
		block = 1;
	}

	baseaddr = baseaddr + block * BLOCK;

	for (i = index; i < block; i++) {
		memorystatus[i].status = BUSY;
	}
	memorystatus[index++].block = block;
	return temp;
}

bool my_free(char *addr)
{
	int tmpidx, i;
	
	if (addr == NULL) return true;
	tmpidx = (addr - memoryhead) / BLOCK;

	if (memorystatus[tmpidx].status == FREE) {
		perror("@@@@@ERROR: Double free @@@@@");
		return false;
	}

	for(i = tmpidx; i < memorystatus[tmpidx].block; i++) {
		memorystatus[i].status = FREE;
	}
	return true;
}

int main()
{
	char *ptr = NULL;

	printf("Initializing\n");
	if (malloc_init() == false) {
		perror("malloc_init() failed");
		return -1;
	}

	printf("Initialization done successfully!!!\n");
	
	ptr = my_malloc(0);

	if (ptr == NULL) {
		perror("my_malloc() failed");
		return -1;
	}
	printf("Allocated memory successfully!!!\n");

	if(my_free(ptr) == false) {
		perror("my_free() failed");
		return -1;
	}
	printf("%p memory freed successfully\n", ptr);
	return 0;
}
