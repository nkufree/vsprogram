#include<iostream>
#include<iomanip>
#include<cstring>
#include<string>
using namespace std;
int main()
{
	while (true)
	{
		uint16_t a, b;
		cin >> a >> b;
		uint16_t c = a - b;
		cout << "a-b=" << c << endl;
	}
	
	return 0;

}