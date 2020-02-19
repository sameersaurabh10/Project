
#include <stdio.h>
#include <string.h>

int max(int a, int b)
{
	return (a> b ? a: b);
}

int lcs_length(char *X, char *Y, int n1, int n2)
{
	if (n1 == 0 || n2 == 0) return 0;
	int value;

	if (X[n1-1] == Y[n2-1]) {
		value =  (lcs_length(X, Y, (n1-1), (n2-1)) +1 );
	} else {
		value =  max(lcs_length(X, Y, n1, (n2-1)), lcs_length(X, Y, (n1-1), n2));
	}
	printf("%d\n", value);
	return value;
}

int main(void)
{
//	char *str1 = "ABCF";
//	char *str2 = "ACF";
//	char *str1 = "ABCBDAB"; 
//	char *str2 = "BDCABA";
	char *str1 = "BDCB";
	char *str2 = "BACDB";
	printf("LCS String : ");
	int res = lcs_length(str1, str2, strlen(str1), strlen(str2));

	if (res > 0) {
		printf("\nLCS : %d\n", res);
	} else {
		printf ("No commou sub-sequece...\n");
	}
	return 0;
}
