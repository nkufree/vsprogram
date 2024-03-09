#include <iostream>
using namespace std;

class Narci 
{
public:
	Narci() {};
	void showNarci(int n)
	{
		int start = 1;
		for (int i = 1; i < n; i++)
			start *= 10;
		int end = start * 10;
		for (int i = start; i < end; i++)
		{
			if (isNarci(i))
				cout << i << " ";
		}
		cout << endl;
	}
	bool isNarci(int n)
	{
		int number = n;
		int* p = new int[100];
		int j = 0;
		while (number != 0)
		{
			p[j++] = number % 10;
			number /= 10;
		}
		int sum = 0;
		for (int i = 0; i < j; i++)
		{
			int pow = 1;
			for (int k = 0; k < j; k++)
				pow *= p[i];
			sum += pow;
		}
		if (sum == n)
			return true;
		else
			return false;
	}
};

int main()
{
	Narci nar;
	nar.showNarci(3);
	nar.showNarci(4);
	if (nar.isNarci(9876))
		cout << "YES";
	else
		cout << "NO";
	return 0;
}