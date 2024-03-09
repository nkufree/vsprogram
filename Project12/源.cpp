#include<iostream>
using namespace std;

long long fib[200] = {};

int main()
{
	int v4 = 0;
	long long sum = 0;
	long long v9, v10, v11, v12;
	fib[0] = 1;
	fib[1] = 1;
	for (int i = 2; i < 200; i++)
	{
		fib[i] = fib[i - 1] + fib[i - 2];
	}
	while (sum != 0x19D024E75FF)
	{
		v4++;
		v9 = fib[v4 - 1];
		sum = 3 * v9 + v4;
		cout << "v4 = " << v4 << " v9 = " << hex << v9 << " sum = " << hex << sum << endl;
	}
	v10 = v9 - 0x233F0E151C;
	v11 = v9 - 0x1B45F81A32;
	v12 = v9 - 0x244C071725;
	cout << "v9 = 0x" << hex << v9 << endl
		<< "v10 = 0x" << hex << v10 << endl
		<< "v11 = 0x" << hex << v11 << endl
		<< "v12 = 0x" << hex << v12 << endl;
	return 0;
}