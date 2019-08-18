/*********************************************************
* parse_int	: converts string to int
*
**********************************************************/

#include <stdio.h>
#include <stdlib.h>

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}


int main()
{
	int res;

	res = parse_int("21233");
	printf("Value : %d\n", res);
	return 0;
}
