#include <iostream>
#include <cmath>

#define CONST 4
using namespace std;

class Node
{
public:
	int totalCreate;
	int totalNum;
	int create;
	Node()
	{
		totalCreate = 0;
		totalNum = 0;
		create = 0;
	}
	Node(int totalCreate, int totalNum):totalCreate(totalCreate),totalNum(totalNum)
	{
		create = 0;
	}

	void print()
	{
		cout << " " << totalCreate << "/" << totalNum << "\t";
	}
};

Node node[3][9] = {};

int search(int deep,int index)
{
	//cout << deep << " " << index;
	double max = 0;
	int nindex = 0;
	if (deep == 1)
	{
		for (int i = index * 3; i < 3 + index * 3; i++)
		{
			if (node[2][i].create > max)
			{
				max = node[2][i].create;
				nindex = i;
			}
		}
		node[2][nindex].totalCreate += node[2][nindex].create;
		node[2][nindex].totalNum++;
		return node[2][nindex].create;
	}
	for (int i = index * 3; i < 3 + index * 3; i++)
	{
		double ucb = node[deep + 1][i].totalCreate * 1.0 / node[deep + 1][i].totalNum 
			+ CONST * sqrt(2 * log(node[deep][i / 3].totalNum) / node[deep + 1][i].totalNum);
		if (ucb > max)
		{
			max = ucb;
			nindex = i;
		}
			
	}
	int t = search(deep + 1, nindex);
	node[deep + 1][nindex].totalCreate += t;
	node[deep + 1][nindex].totalNum++;
	if (deep == 0)
	{
		node[0][0].totalCreate += t;
		node[0][0].totalNum++;
	}
	return t;
}


int main()
{
	
	int createl[9] = { 1,9,5,6,2,7,3,4,5 };
	for (int i = 0; i < 13; i++)
	{
		int tc = 0;
		int tn = 0;
		cin >> tc >> tn;
		if (i == 0)
			node[0][0] = Node(tc, tn);
		else if (i < 4)
			node[1][i - 1] = Node(tc, tn);
		else
			node[2][i - 4] = Node(tc, tn);
	}
	for (int i = 0; i < 9; i++)
		node[2][i].create = createl[i];
	
	for (int i = 0; ; i++)
	{
		search(0, 0);
		cout << "µü´úµÚ" << i + 1 << "´Î" << endl;
		node[0][0].print();
		cout << endl;
		for(int j = 0; j < 3; j++)
			node[1][j].print();
		cout << endl;
		for (int j = 0; j < 9; j++)
			node[2][j].print();
		cout << endl;
		cout << "----------------------------------" << endl;
		if (node[2][1].totalNum == 10)
			break;
	}
}

/*
29 7
1 1 21 4 7 2
0 0 0 0 0 0 6 1 2 1 7 1 3 1 0 0 0 0

*/