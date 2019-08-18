/***********************************************************
* ltrim	:	Removes white space from left side of string
*
*
************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}



int main()
{
	char *str = "  Hello world    ";

	printf("Start of string !!!");
	printf("%s\n", str);
	printf("String : %s", ltrim(str));
	printf("!!! End of string\n");
	return 0;
}
