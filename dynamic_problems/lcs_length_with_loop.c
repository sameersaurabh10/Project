#include <stdio.h>
#include <string.h>


int lcs_length(char *X, char *Y, int n1, int n2)
{
	int i, j, k, size = 0;
	int count = 0, max = 0;
	char temp[n1+1];

	for (i = 0; i < n1; i++) {
		k = i;
		count = 0;
		for (j = 0; j<n2; j++) {
			if(X[k] == Y[j]) {
				temp[size++] = X[j];
				k++;
				count++;
			}
		}
		temp[size++] = '-';
		max = max>count? max : count;
	}
	temp[size-1] = '\0';
	printf("LCS : %s\n", temp);
	return max;
}

int main(void)
{
	char *str1 = "ABCBDAB";
	char *str2 = "BDCABA";
	int res = lcs_length(str1, str2, strlen(str1), strlen(str2));
	printf("LCS length : %d\n", res);
	return 0;
}
