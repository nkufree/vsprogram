#include <iostream>
#include <cstring>
using namespace std;

template <class T>
class Sort
{
public:
	T* m_p;
	int m_len;
	Sort(T* p, int len):m_len(len)
	{
		m_p = new T[len];
		for (int i = 0; i < len; i++)
		{
			for (int j = len - 1; j > i; j--)
			{
				if (*(p + j) < *(p + j - 1))
				{
					T q = *(p + j);
					*(p + j) = *(p + j - 1);
					*(p + j - 1) = q;
				}
			}
		}
		m_p = p;
	}
};

int main()
{
	int len;

	cin >> len;
	int* p1 = new int[len];
	for (int i = 0; i < len; i++)
		cin >> *(p1 + i);
	Sort<int> sort1(p1, len);

	cin >> len;
	char* p2 = new char[len];
	for (int i = 0; i < len; i++)
		cin >> *(p2 + i);
	Sort<char> sort2(p2, len);

	cin >> len;
	string* p3 = new string[len];
	for (int i = 0; i < len; i++)
		cin >> *(p3 + i);
	Sort<string> sort3(p3, len);
	
	cout << *sort1.m_p;
	for (int i = 1; i < sort1.m_len; i++)
		cout << " " << *(sort1.m_p + i);
	cout << endl;

	cout << *sort2.m_p;
	for (int i = 1; i < sort2.m_len; i++)
		cout << " " << *(sort2.m_p + i);
	cout << endl;

	cout << *sort3.m_p;
	for (int i = 1; i < sort3.m_len; i++)
		cout << " " << *(sort3.m_p + i);

}