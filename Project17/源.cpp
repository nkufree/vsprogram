#include<iostream>
int add(int x, int y)
{
	int z = 0;
	z = x + y;
	return z;
}
void main()
{
	int n = 0;
	n = add(1, 3);
	printf("%d\n", n);
}