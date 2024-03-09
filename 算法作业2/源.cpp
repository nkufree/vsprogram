#include<iostream>
#include<list>
#include<vector>
using namespace std;
int main()
{
	int graph[50][50] = {};
	int v, e;
	cin >> v >> e;
	int recyc = -1;
	for (int i = 0; i < e; i++)
	{
		int start, end;
		cin >> start >> end;
		graph[start-1][end-1] = 1;
		if (start == end)
			recyc = start;
	}
	if (recyc != -1)
	{
		cout << "NO" << endl
			<< recyc << "," << recyc;
		return 0;
	}
	list<int> notSort = {};
	vector<int> vSort = {};
	for (int i = 0; i < v; i++)
		notSort.push_back(i);
	list<int>::iterator it = notSort.begin();
	while(notSort.size() != 0)
	{
		int flag = 1;
		for (int i = 0; i < v; i++)
		{
			if (graph[i][*it] != 0)
			{
				flag = 0;
				break;
			}
		}
		if (flag == 0)
		{
			it++;
			if (it == notSort.end())
			{
				it = notSort.begin();
				int st = *it;
				int curr = st;
				int next = -1;
				cout << "NO" << endl 
					<< st + 1;
				while (next != st)
				{
					for (int i = 0; i < v; i++)
					{
						if (graph[curr][i] == 1)
						{
							next = i;
							cout << "," << next + 1;
							curr = next;
							break;
						}
					}
				}
				return 0;
			}
		}
		else
		{
			vSort.push_back(*it);
			for (int i = 0; i < v; i++)
				graph[*it][i] = 0;
			notSort.erase(it);
			it = notSort.begin();
		}
	}
	cout << "YES" << endl;
	cout << vSort[0] + 1;
	for (int i = 1; i < vSort.size(); i++)
		cout << "," << vSort[i] + 1;
	return 0;
}