#include<iostream>
#include<iomanip> 
#include<queue>
#include <vector>
#include<algorithm>
#include<stdio.h>
using namespace std;

void jisuan(vector<double> v, double& sum)
{
	while (v.size() > 1)
	{
		sum += v[0] + v[1];
		double temp1 = v[0];
		double temp2 = v[1];
		v.erase(v.begin(), v.begin() + 2);

		int m = 0;
		vector<double>::iterator it = v.begin();
		while (it != v.end() && temp1 + temp2 > *it)
		{
			m++;
			it++;
		}
		v.insert(v.begin() + m, 1, temp1 + temp2);


		//v.push_back(temp1 + temp2);
		//sort(v.begin(), v.end());
	}
	return;
}


int main()
{
	double Sum_p = 0;
	double n;
	cin >> n;
	vector<double> v;
	while (n--)
	{
		double x;
		cin >> x;
		v.push_back(x);
		Sum_p = Sum_p + x;

	}
	sort(v.begin(), v.end());
	double sum = 0;
	jisuan(v, sum);
	cout.setf(ios::fixed);
	cout << setprecision(2) << sum / Sum_p;
	return 0;

}