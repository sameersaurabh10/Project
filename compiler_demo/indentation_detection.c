#include <stdio.h>
#include <ctype.h>

int main()
{
	FILE *fp = NULL;
	char line[256];
	int i, space_count, error, texts, text_line, j, tab_count;
	char *temp;

	fp = fopen("input.txt", "r");
	if (fp == NULL) {
		printf("Failed to open file\n");
		return -1;
	}
	
	while (fgets(line, sizeof(line), fp)) {
		i = 0, space_count = 0, error = 0, texts = 0;
		text_line++, tab_count = 0;

		printf("Read line : %s\n", line);
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
						printf("WARN : Trailing spaces present at Line : %d, columns : %d \n", text_line, i);
						break;
					}
				}
			} else if (isalpha(line[i])) {
				if ( tab_count > 1 && texts == 0) {
					error = -1;
					printf("WARN<TAB> : Trailing tab spaces are more than expected,Line : %d, columns : %d \n", text_line, i);
					break;
				} 

				if ( (space_count > 0 &&  space_count < 4) && texts == 0) {
					error = -1;
					printf("WARN<SPACE> : Trailing spaces present at Line : %d, columns : %d \n", text_line, i);
					break;
				}

				space_count = 0;
				tab_count = 0;
				texts++;
			}
			i++;
		}
		if (error !=0) break;
	}
	return 0;
}
