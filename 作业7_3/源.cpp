#include <iostream>
#include <cstring>
using namespace std;
class Rational
{
public:
	int a;
	int b;
	Rational(string str = "");
	void reduce();
	Rational operator +(Rational& r1);
	Rational operator -(Rational& r1);
	Rational operator ++(int);
	friend Rational operator *(Rational& r1, Rational& r2);
	friend Rational operator /(Rational& r1, Rational& r2);
	Rational operator =(Rational& r1);
	friend void operator <<(ostream &cout, Rational& r);
};

Rational::Rational(string str)
{
	if (str == "")
	{
		a = 0;
		b = 1;
	}
	else
	{
		a = 0;
		b = 0;
		int i = 0;
		for (i = 0; str[i] != '/'; i++)
		{
			a = a * 10 + str[i] - '0';
		}
		for (i = i + 1; i < str.size(); i++)
		{
			b = b * 10 + str[i] - '0';
		}
		reduce();
	}
}

void Rational::reduce()
{
	int flag = 1;
	if (a < 0)
	{
		a = -a;
		flag = -1;
	}
	int t = a < b ? a : b;
	if (t == 1)
		return;
	for (int i = t; i >= 1; i--)
	{
		if (a % i == 0 && b % i == 0)
		{
			a = a / i * flag;
			b = b / i;
			return;
		}
	}
}

Rational Rational::operator +(Rational& r1)
{
	Rational r;
	r.a = r1.a * b + a * r1.b;
	r.b = r1.b * b;
	r.reduce();
	cout << r;
	return r;
}
Rational Rational::operator -(Rational& r1)
{
	Rational r;
	r.a = a * r1.b - r1.a * b;
	r.b = r1.b * b;
	r.reduce();
	cout << r;
	return r;
}
Rational Rational::operator ++(int)
{
	a = a + b;
	cout << *this;
	return *this;
}
Rational operator *(Rational& r1, Rational& r2)
{
	Rational r;
	r.a = r1.a * r2.a;
	r.b = r1.b * r2.b;
	r.reduce();
	cout << r;
	return r;
}
Rational operator /(Rational& r1, Rational& r2)
{
	Rational r;
	r.a = r1.a * r2.b;
	r.b = r1.b * r2.a;
	r.reduce();
	cout << r;
	return r;
}
Rational Rational::operator =(Rational& R1)
{
	Rational R2;
	R2.a = R1.b;
	R2.b = R1.a;
	cout << R2;
	return R2;
}
void operator <<(ostream& cout, Rational& r)
{
	if (r.a == 0)
		cout << "0";
	else if (r.b == 1)
		cout << r.a;
	else
		cout << r.a << "/" << r.b;
}

int main()
{
	int n;
	cin >> n;
	int opt[50]{};
	string s[50][2]{};
	for (int i = 0; i < n; i++)
	{
		cin >> opt[i];
		if (opt[i] <= 4)
		{
			cin >> s[i][0] >> s[i][1];
		}
		else
			cin >> s[i][0];		
	}
	for (int i = 0; i < n; i++)
	{
		if (opt[i] <= 4)
		{
			Rational r1(s[i][0]);
			Rational r2(s[i][1]);
			switch (opt[i])
			{
			case 1:
				r1 + r2;
				break;
			case 2:
				r1 - r2;
				break;
			case 3:
				r1 * r2;
				break;
			case 4:
				r1 / r2;
			}
		}
		else
		{
			Rational r(s[i][0]);
			if (opt[i] == 5)
				r++;
			else if (opt[i] == 6)
				r = r;
		}
		cout << endl;
	}
	return 0;
}