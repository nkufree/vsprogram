#include<iostream>
#include<cmath>
using namespace std;

int dis[2][4000] = {};

int min3(int a, int b, int c) {
	a = a < b ? a : b;
	return a < c ? a : c;
}

int getDis(string s1, string s2, int k)
{
	for (int i = 0; i < s1.length(); i++)
		dis[0][i + 1] = k * i + k;
	for(int i = 0; i < s2.length(); i++)
	{
		//for (int j = 0; j <= s1.length(); j++)
		//	cout << dis[0][j] << " ";
		//cout << endl;
		dis[1][0] = dis[0][0] + k;
		for (int j = 0; j < s1.length(); j++)
		{
				dis[1][j + 1] = min3(dis[0][j] + abs(int(s1[j] - s2[i])), dis[0][j + 1] + k, dis[1][j] + k);
		}
		dis[0][0] = k * (i + 1);
		for (int j = 0; j < s1.length(); j++)
			dis[0][j + 1] = dis[1][j + 1];
	}
	//for (int j = 0; j <= s1.length(); j++)
	//	cout << dis[1][j] << " ";
	//cout << endl;
	return dis[1][s1.length()];
}

int main()
{
	string a, b;
	int k;
	cin >> a >> b >> k;
	int minDis;
	minDis = getDis(b, a, k);
	cout << minDis << endl;
	return 0;
}