#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void find_char_sequence_and_print(char *arr, int n, int k, char *prefix, int buffsiz);

void print_all_char_sequence(char *arr, int k)
{
	int len = strlen(arr);
	find_char_sequence_and_print(arr, len, k, NULL, k + 1);
}

void find_char_sequence_and_print(char *arr, int n, int k, char *prefix, int buffsiz)
{
	int i, len;
	char *temp = (char *) malloc (buffsiz);

	if ( k == 0) {
		printf("> %s\n", prefix);
		if(temp) {
			free(temp);
			temp = NULL;
		}
		return;
	}

	for (i = 0; i < n; i++) {
		if(prefix) 
			sprintf(temp, "%s", prefix);
		len = strlen(temp);
		sprintf(temp+len, "%c", arr[i]);
		len = strlen(temp);
		temp[len+1] = '\0';
		find_char_sequence_and_print(arr, n, k - 1, temp, buffsiz);
		memset(temp, 0, buffsiz);
	}
}

int main()
{
	char arr[] = "ab";
	int k = 2;
	printf("Program starts...\n");
	print_all_char_sequence(arr, k);
	printf("Program ends...\n");
	return 0;
}
