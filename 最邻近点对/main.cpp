#include<iostream>
#include<algorithm>
#include<cmath>
#include<iomanip>
#include<vector>
using namespace std;

struct point
{
	double x;
	double y;
};

point points[30001] = {};

bool cmp(point p1, point p2)
{
	if (p1.x != p2.x)
		return p1.x < p2.x;
	else
		return p1.y < p2.y;
}
bool cmpy(point p1, point p2)
{
	return p1.y < p2.y;
}

double distance(point p1, point p2)
{
	return (p1.x - p2.x)* (p1.x - p2.x) + (p1.y - p2.y)* (p1.y - p2.y);
}

double digui(int left,int right)
{
	double dis = 200000001;
	if (right - left == 1)
		return distance(points[left], points[right]);
	else if (right - left == 2)
	{
		double tdis1 = distance(points[left], points[left+1]);
		double tdis2 = distance(points[left], points[right]);
		double tdis3 = distance(points[left + 1], points[right]);
		double mindis = tdis1 > tdis2 ? (tdis2 > tdis3 ? tdis3 : tdis2) :
			tdis1 > tdis3 ? tdis3 : tdis1;
		return mindis;
	}
	int mid = (left + right) / 2;
	double dis1 = digui(left, mid);
	double dis2 = digui(mid + 1, right);
	dis = min(dis1, dis2);
	double dis3 = 200000001;
	
	double midx = points[mid].x;
	vector<point> tempv;
	for (int i = mid; i >= left && pow(midx - points[i].x, 2) < dis; i--)
		tempv.push_back(points[i]);
	for (int i = mid + 1; i <= right && pow(midx - points[i].x, 2) < dis; i++)
		tempv.push_back(points[i]);
	sort(tempv.begin(), tempv.end(), cmpy);
	int num = tempv.size();
	for (int i = 0; i < num; i++)
	{
		for (int j = i + 1; j < num; j++)
		{
			if (pow(tempv[i].y - tempv[j].y, 2) >= dis)
				break;
			else
				dis3 = min(dis3, distance(tempv[i], tempv[j]));
		}
	}
	dis = min(dis, dis3);
	return dis;
}

int main()
{
	int count = 0;
	cin >> count;
	for (int i = 0; i < count; i++)
		cin >> points[i].x >> points[i].y;
	sort(&points[0], &points[count], cmp);
	double disMin = 0;
	disMin = digui(0, count - 1);
	cout << fixed << setprecision(2) << disMin;
	return 0;
}