#include <iostream>
#include <cmath>
using namespace std;
class Distance
{
public:
	long dis;
	Distance(){}
	virtual long getDistance() { return dis; }
};
class ManhattanDistance :public Distance
{
public:
	ManhattanDistance(int x1, int y1, int x2, int y2)
	{
		getDistance(x1, y1, x2, y2);
	}
	long getDistance(int x1, int y1, int x2, int y2)
	{
		dis = abs(x1 - x2) + abs(y1 - y2);
		return dis;
	}
};
class EuclideanDistance :public Distance
{
public:
	EuclideanDistance(int x1, int y1, int x2, int y2)
	{
		getDistance(x1, y1, x2, y2);
	}
	long getDistance(int x1, int y1, int x2, int y2)
	{
		dis = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
		return dis;
	}
};

int main()
{
	int x1, y1, x2, y2;
	cin >> x1 >> y1 >> x2 >> y2;
	Distance* arr[2];
	ManhattanDistance mh(x1, y1, x2, y2);
	EuclideanDistance el(x1, y1, x2, y2);
	arr[0] = &mh;
	arr[1] = &el;
	cout << arr[0]->dis << " " << arr[1]->dis;
	return 0;
}