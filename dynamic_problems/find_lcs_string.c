#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dump_array(int T[6][5], int n1, int n2)
{
	int k, l;
	printf("\nLCS Array output \n");
	for( k = 0; k <=n1;k++) {
		for (l = 0; l <=n2;l++) {
			printf("%d ",T[k][l]);
		}
		printf("\n");
	}
	printf("\n");
}

char *print_lcs(int T[6][5], char *Y, int row, int col, char *res)
{

	if (row == 0 && col == 0) return NULL;

	if (T[row - 1][col] == T[row][col - 1]) {
		if (T[row][col] > T[row][col -1 ]) {
			printf("res : %s\n", res);
			if(strlen(res) > 0)
				sprintf(res,"%c%s", Y[row-1], res);
			else 
				sprintf(res, "%c", Y[row-1]);
			printf("res : %s\n", res);
			print_lcs(T, Y, row - 1, col - 1, res);
		} else {
			print_lcs(T, Y, row - 1, col, res);
		}
	} else if (T[row - 1][col] >= T[row][col - 1]){
		print_lcs(T, Y, row - 1, col, res);
	} else {
		print_lcs(T, Y, row, col - 1, res);
	}

	return res;
}

#define MAX(x,y) x > y ? x: y

int main()
{
	printf("Program starts\n");
	char *str1 = "BACDB";
	char *str2 = "BDCB";
	int i, j;
	char *res = (char *) malloc(5);

	int n1 = strlen(str1);
	int n2 = strlen(str2);
	int T[n1+1][n2+1];

	//Logic to fill array with 0
	for( i = 0; i <= n1; i++) {
		for(j = 0; j <= n2; j++) {
			T[i][j] = 0;
		}
	}

	//Logic to generate LCS multi-Dimenssional array
	for (i = 1; i <= n1; i++) {
		for ( j = 1; j <= n2; j++) {
			if (str1[i-1] == str2[j-1])
				T[i][j] = T[i-1][j-1] + 1;
			else
				T[i][j] = MAX(T[i-1][j],T[i][j-1]);				
		}
	}

	dump_array(T,n1, n2);
	char *result = NULL;
	//Make sure str1 length is always greater
	result = print_lcs(T, str1, i-1, j-1, res);
	if(result)
		printf("LCS : %s\n", result);

	printf("Program ends\n");
	return 0;
}
