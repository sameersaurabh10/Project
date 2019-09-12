#include <stdio.h>

int a1;
int a2=10;
extern int b1;
extern int b2;
static int c1;
static int c2=30;
const int d1;
const int d2=40;
static const int e1;
static const int e2=10;

int main()
{
	int f1;
	extern int g1;
	static int h1;
	static int h2 = 10;
	const int i1;
	const int i2 = 103;
	static const int j1;
	static const int j2 = 434;

	{
		static int m1;
		static int m2 = 40;
		const int n1;
		const int n2 = 40;
		int r1;
		int r2;
	}
	return 0;
}
