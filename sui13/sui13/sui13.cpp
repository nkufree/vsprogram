#include<iostream>
using namespace std;

int factorial(int n)
{
	long long sum = 1;
	if (n == 1)
		return 1;
	for (int i = 2; i <= n; i++)
		sum *= i;
	return sum;
}

int main()
{
	//double n = 0;
	//long long sum = 0;
	//cin >> n;
	//if (n != static_cast<double>(static_cast<int>(n)) || n <= 0)
	//	cout << "Incorrect input!" ;
	//else
	//{
	//	for (int i = 1; i <= n; i++)
	//		sum += factorial(i);
	//	if (sum > 2147483647 || sum < -2147483648)
	//		cout << "Out of range!" ;
	//	else
	//		cout << sum;
	//}
	//return 0;
	cout<< factorial(12)*13;
}