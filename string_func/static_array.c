#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define BUFF_SIZE 128

char *readline()
{
    char *line = NULL;
    line = (char *) malloc(sizeof(char));
    if((line = fgets(line, BUFF_SIZE, stdin)) == NULL) {
        return NULL;
    }
    return line;
}

int str_to_int(char *str) 
{
    char *endptr;
	printf("Input : %s\n", str);	
    int value = strtol(str, &endptr, 10);
    if (!(endptr == str || *endptr != '\0')) {
        return -1;
    }   
    free(str);
    return value;
}
int main() {
    
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    char *buff = NULL;
    int *arr = NULL;
    int value, temp;

    buff = readline();
    value = str_to_int(buff);
	
    arr = (int *) malloc(value * sizeof(int));

    int i, sum = 0;
    for (i = 0; i < value; i++ ) {
        buff = readline();
        temp = str_to_int(buff);
        sum = sum + temp;
		arr[i] = temp;
    }
    printf("%d\n", sum);

    return 0;
}


