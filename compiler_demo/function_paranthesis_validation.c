#include <stdio.h>
#include <ctype.h>

int check_indentation(char *line, int line_number)
{
	int i, space_count, error, texts, j, tab_count;
	char *temp;

	i = 0, space_count = 0, error = 0, texts = 0;
	line_number++, tab_count = 0;

	while(line[i] != '\0') {
		if (line[i] == ' ') {
			space_count++;
			if (texts > 0) {
				j= i + 1;
				temp = line;
				while(temp[j] != '\0') {
					if (isalpha(temp[j++])) {
						space_count=0;
						break;
					}
				}
				if (space_count > 0) {
					error = -1;
					printf("WARN : Trailing spaces are present\n");
					break;
				}
			}
			if (space_count >4 && texts == 0) {
				error = -1;
				printf("WARN<1> : Line is not aligned\n");
				break;
			}
		} else if (line[i] == '\t') {
			tab_count++;
			if (texts > 0) {
				j= i + 1;
				temp = line;
				while(temp[j] != '\0') {
					if (isalpha(temp[j++])) {
						tab_count=0;
						break;
					}
				}
				if(tab_count > 0) {
					error = -1;
					printf("WARN : Trailing spaces present at Line : %d, columns : %d \n", line_number, i);
					break;
				}
			}
		} else if (isalpha(line[i])) {
			if ( tab_count > 1 && texts == 0) {
				error = -1;
				printf("WARN<TAB> : Trailing tab spaces are more than expected,Line : %d, columns : %d \n", line_number, i);
				break;
			} 
				if ( (space_count > 0 &&  space_count < 4) && texts == 0) {
				error = -1;
				printf("WARN<SPACE> : Trailing spaces present at Line : %d, columns : %d \n", line_number, i);
				break;
			}
			space_count = 0;
			tab_count = 0;
			texts++;
		}
		i++;
	}
	if (error !=0) 
		return -1;;
	return 0; //Success
}

int main()
{
	FILE *fp = NULL;
	char line[256];
	int line_number, status;

	fp = fopen("input.txt", "r");
	if (fp == NULL) {
		printf("Failed to open file\n");
		return -1;
	}
	while (fgets(line, sizeof(line), fp)) {
		line_number++;
		status = check_indentation(line, line_number);
		
		if (status) {
			printf("MAIN : Indentation is corect check to provided place\n");
			return -1;
		}
	}


	return 0;
}
