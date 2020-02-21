#include <stdio.h>

enum {
	SPACE,
	VERTAB,
	HORTAB,
	NEWLINE,
	NOTSPACE
} spaces;

static int line_count = 0;

int chec_spaces(char ch)
{
	if (ch == ' ') return SPACE;
	else if (ch == '\t') return HORTAB;
	else if (ch == '\v') return VERTAB;
	else return NOTSPACE;
}

void check_indentation(char *ptr)
{
	int curly_braces = 0;
	int before_spaces = 0;
	int after_spaces = 0;

	while(*ptr != '\n'){
		if (before_space+=chec_spaces(*ptr)) {
		}				
		ptr++;
	}
}

int main()
{
	FILE *fp = NULL;
	char line[256];

	fp = popen("input.txt", "r");
	if (fp == NULL) {
		printf("Failed to open file\n");
		return -1;
	}
	
	while (fgets(line, sizeof(line), fp)) {
		check_indentation(line);
	}
	return 0;
}
