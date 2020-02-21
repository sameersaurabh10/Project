#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0


int validate_dob(int dd, int mm, int yy)
{
	if(!(dd > 0 && dd <= 31))
		return false;

	if(!(mm >= 1 && mm <= 12))
		return false;

	if(!(yy > 999 && yy <= 9999))
		return false;
	
	return true;
}

int convert_to_number(char *data, char *buff)
{
	int dd, mm, yy;

	if(!data)
		return false;

	sscanf(data, "%d%*c%d%*c%d", &dd, &mm, &yy);

	if (!validate_dob(dd, mm, yy))
		return false;
	sprintf(buff, "%d%d%d", dd, mm, yy);

	return true;
}

int getDigitSum(int data) 
{
	int sum = 0;
	while(data > 0) {
		sum = sum + data % 10;
		data = data / 10;
	}
	return sum;
}
int getLuckyNumber(int data) 
{
	int res;

		res = getDigitSum(data);
		if(res >=0 && res <10)
			return res;
		return getLuckyNumber(res);
}

int main() 
{
	int res;
	char data[10], buff[8];

	printf("Enter DOB : ");
	scanf("%s", data);
	printf("Given DOB : %s\n", data);
	
	if(!convert_to_number(data, buff)) {
		printf("Provide correct DOB format\n");
		return false;
	}

	res = getLuckyNumber(atoi(buff));
	printf("Lucky Number : %d\n",  res);

	return 0;	
}
