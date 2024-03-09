#include<iostream>
using namespace std;

int main()
{
	char a;
	while (cin >> a)
	{
		cout << int(a - 'a' + 1) << endl;
	}
	return 0;
}