/********************************************************
* rtrim	:	removes white space from right os string
*
********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* rtrim(char* str) {
	
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str);
	printf("str len : %d\n", (int)strlen(str));

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';
    return str;
}

int main()
{
	char *str = "Hello world   ";

	printf("Before : %s\n", str);
	printf("After : %s", rtrim(str));
	printf("!!! End of string\n");
	return 0;
}
