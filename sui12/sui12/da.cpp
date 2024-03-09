#include<iostream>
using namespace std;
char S[5000], s[5000];

bool clear(int a, int length)
{
	for (int i = a; i < a + length; i++)
	{
		if (S[i] != s[i - a])
			return 0;
	}
	for (int i = a; i < a + length; i++)
	{
		S[i] = ' ';
	}
	return 1;
}

int main()
{
	cin >> S >> s;
	int length;
	for (length = 0; s[length] != '\0'; length++);
	for (int i = 0; S[i] != '\0'; i++)
		clear(i, length);
	for (int i = 0; S[i] != '\0'; i++)
	{
		if (S[i] != ' ')
			cout << S[i];
	}
	return 0;
}