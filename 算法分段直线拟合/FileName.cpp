#include<iostream>
#include<algorithm>
#include<iomanip>
#define MAX_POINT 1001

using namespace std;


struct Point 
{
	double x;
	double y;
} points[MAX_POINT];

double errors[MAX_POINT][MAX_POINT] = {};
double m[MAX_POINT] = {};

double calError(int i, int j)
{
	int n = j - i + 1;
	double sumxy = 0;
	double sumx = 0;
	double sumy = 0;
	double sumx2 = 0;
	for (int k = i; k <= j; k++)
	{
		sumxy += points[k].x * points[k].y;
		sumx += points[k].x;
		sumy += points[k].y;
		sumx2 += points[k].x * points[k].x;
	}
	double a = (n * sumxy - sumx * sumy) / (n * sumx2 - sumx * sumx);
	double b = (sumy - a * sumx) / n;
	double sume2 = 0;
	for (int k = i; k <= j; k++)
	{
		double e = points[k].y - a * points[k].x - b;
		sume2 += e * e;
	}
	return sume2;	
}

bool cmp(Point* p1,Point* p2)
{
	return p1->x < p2->x;
}

int main()
{
	int count = 0;
	double c;
	cin >> count >> c;
	for (int i = 1; i <= count; i++)
		cin >> points[i].x >> points[i].y;
	//sort(points, points + count, cmp);
	for (int i = 1; i <= count; i++)
		for (int j = i + 1; j <= count; j++)
			errors[i][j] = calError(i, j);
	
	m[0] = 0;
	for (int i = 1; i <= count; i++)
	{
		double min = 9999999999;
		for (int j = 1; j <= i; j++)
		{
			double temp = errors[j][i] + m[j - 1] + c;
			if (temp < min)
			{
				min = temp;
				//cout << errors[j][i] << "  " << m[j - 1] << " " << j << " " << i << endl;
			}
		}
		m[i] = min;
	}
	cout << fixed << setprecision(2) << m[count] << endl;
	
	return 0;
}