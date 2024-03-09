#include <iostream>
#include <cstring>
using namespace std;

template <class T>
void Print(T* p, int n)
{
	cout << *(p + 0);
	for (int i = 1; i < n; i++)
	{
		cout << "&" << *(p + i);
	}
}
template <class T>
void GetLever(T* p, int n, T lever)
{
	int count = 0;
	for (int i = n - 1; i >= count; i--)
	{
		if (*(p + i) > lever)
		{
			T q = *(p + i);
			for (int j = i; j > 0; j--)
			{
				*(p + j) = *(p + j - 1);
			}
			*p = q;
			count++;
			i++;
		}
	}
	Print(p, count);
}

int main()
{
	string s;
	int len, n;
	cin >> s >> len >> n;
	if (s == "int")
	{
		int* p = new int[len];
		int lever;
		for (int i = 0; i < len; i++)
			cin >> *(p + i);
		cin >> lever;
		GetLever(p, n, lever);

	}
	else if (s == "float")
	{
		float* p = new float[len];
		float lever;
		for (int i = 0; i < len; i++)
			cin >> *(p + i);
		cin >> lever;
		GetLever(p, n, lever);
	}
	else if (s == "char")
	{
		char* p = new char[len];
		char lever;
		for (int i = 0; i < len; i++)
			cin >> *(p + i);
		cin >> lever;
		GetLever(p, n, lever);
	}
	return 0;
}