/****************************************************************
* split_string	:	Function to split the string based on single 
*					delimeter delimeter.
*
****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** split_string(char* str, char *del) {
    char** splits = NULL;
    char* token = strtok(str, del);

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, del);
    }

    return splits;
}



int main()
{
	char *str = "ABC DEF  MNO  FDEG KDL  KDSLL";
	
	char **result = NULL;
	char *del = " ";
	int i = 0;
	
	result = split_string(str, del);
	if(result == NULL) {
		printf ("Failed to split string based on space delimeter\n");
		return -1;
	}

	while(result[i]) {
		printf("result[%d] : %s\n", i, result[i]);
		i++;
	}
	return 0;
}

