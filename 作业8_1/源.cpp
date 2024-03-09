#include <iostream>
using namespace std;

class String
{
public:
	String() {};
	char str[100]{};
	String(const char *stri){
		for (int i = 0; stri[i] != 0; i++)
		{
			str[i] = stri[i];
		}
	}
	char* getStr() {
		return str;
	}
	int getLen() {
		int len = 0;
		for (len = 0; str[len] != '\0'; len++);
		return len;
	}
};

class EditableString:public String
{
public:
	EditableString(const char* stri) 
	{
		for (int i = 0; stri[i] != 0; i++)
		{
			str[i] = stri[i];
		}
	}
	bool edit(char s, double m, char t)
	{
		int len = getLen();
		if (s == 'i')
		{
			if (m <= 0 || m > len + 1 || (int)m != m)
				return false;
			for (int i = len; i >= (int)m; i--)
			{
				str[i] = str[i - 1];

			}
			str[(int)m - 1] = t;
			return true;
		}
		else if (s == 'r')
		{
			if (m <= 0 || m > len || (int)m != m)
				return false;
			else
			{
				str[(int)m - 1] = t;
				return true;
			}
		}
	}
	bool edit(char s, double m)
	{
		int j = 0;
		int len = getLen();
		if (m <= 0 || m > len || (int)m != m)
				return false;
			else
			{
				for (int i = (int)m - 1; i < len - 1; i++)
				{
					str[i] = str[i + 1];
				}
				str[len - 1] = '\0';
				return true;
			}
	}
};

int main()
{
	EditableString str("1234567890");
	char strr[100][100]{};
	int i = 1;
	for (int k = 0; k < 9; k++)
		strr[0][k] = '0' + k + 1;
	strr[0][9] = '0';
	for (i = 1; ; i++)
	{
		char s;
		cin >> s;
		if (s == 'i' || s == 'r')
		{
			double d;
			char m;
			cin >> d >> m;
			if (str.edit(s, d, m))
			{
				for (int j = 0; str.str[j] != '\0'; j++)
					strr[i][j] = str.str[j];
			}
			else
			{
				for (int j = 0; strr[i - 1][j] != '\0'; j++)
					strr[i][j] = strr[i - 1][j];
			}
		}
		else if (s == 'd')
		{
			int d;
			cin >> d;
			if (str.edit(s, d))
			{
				for (int j = 0; str.str[j] != '\0'; j++)
					strr[i][j] = str.str[j];
			}
			else
			{
				for (int j = 0; strr[i - 1][j] != '\0'; j++)
					strr[i][j] = strr[i - 1][j];
			}
		}
		else
			break;
	}
	for (int j = 1; j < i; j++)
		cout << strr[j] << " ";
}