#include<iostream>
#include<fstream>
#include<cmath>
#define pai 3.1412
#define radius 27.122
using namespace std;

double a[100][9] = {};

double f(double x, double y)
{
	int k;
	for (int i = 0; i < 32; i++)
	{
		if (x >= a[i][0] && x < a[i][1] && y >= a[i][2] && y < a[i][3])
		{
			k = i;
		}
	}
	double z = a[k][4] + a[k][5] * x + a[k][6] * x * x + a[k][7] * y + a[k][8] * y * y;
	if (z < 0)
		z = 0.0;
	return z;
}

int main()
{
	ifstream myfile("res.txt");
	for (int i = 0; i < 32 ; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			myfile >> a[i][j];
		}
		
	}
	for(int i = 31; i >= 0; i--)
		cout << a[i][0] << "<x<" << a[i][1] << "&&"
		<< a[i][2] << "<y<" << a[i][3]
		<< "," << a[i][4]
		<< "+" << a[i][5] << "*x"
		<< "+" << a[i][6] << "*x^2"
		<< "+" << a[i][7] << "*y"
		<< "+" << a[i][8] << "*y^2" << ",";

	myfile.close();
	double step1 = 0.001;
	double step2 = 0.001;
	double sum = 0.0;
	for (double a = 0.0; a <= 2 * pai; a += step1)
	{
		for (double r = 0.0; r <= radius; r += step2)
		{
			double z = f(r * cos(a), r * sin(a));
			double V = step2 * step1 * r * z;
			sum += V;
		}
	}
	cout << "总体积为" << sum;
	return 0;
}