#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
	int array[13] = { 0,1,2,3,4,5,6,7,8,9,10,11,12 };
	int k,a = 1,b = 0;
	cin >> k;
	for (int i = 1; i < 12; i++)
	{
		while(b != k)
		{
			if (a == 13)
				a = 1;
			if (array[a] != 0)
				b++;
			a++;
		}
		array[a - 1] = 0;
		for (int j = 1; j < 13; j++)
			cout << setw(3) << array[j];
		cout << endl;
		b = 0;
	}
	for (int i = 1; i < 13; i++)
	{
		if (array[i] != 0)
			cout << setw(3) << array[i];
	}
	return 0;
}