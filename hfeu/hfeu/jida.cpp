#include<iostream>
#include<iomanip>
using namespace std;

int main()
{
	int year, day, month,sum=0,i,s;
	cin >> year >> day >> month;
	if (year % 400 == 0 || year % 4 == 0 && year % 100 != 0)
		i = 29;
	else
		i = 28;
	if (day >= 0 && day < 7 && month>0 && month < 13)
	{
		int a[13] = {0,31,i,31,30,31,30,31,31,30,31,30,31};
		s = a[month];
		for (int k = 0; k < month; k++)
			sum += a[k];
		int blank = (sum + day) % 7;
		int array[39] = {};
		for (int k = blank + 1; k <= blank + s; k++)
			array[k] = k - blank;
		for (int k = 1; k <= blank + s; k++)
		{
			if (array[k] == 0)
				cout << setw(4) << " ";
			else
				cout << setw(4) << array[k];
			if (k % 7 == 0)
				cout << endl;
		}
	}
	else
		cout << "ERROR" << endl;
}