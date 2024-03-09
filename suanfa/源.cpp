#include<iostream>
#include<queue>
#include<list>
using namespace std;
class Node {
public:
	int num;
	int enter;
	int exit;
	int* front;
	int front_num;
	int* last;
	int last_num;
	Node() {
		num = 0;
		enter = 0;
		exit = 0;
		front_num = 0;
		last_num = 0;
		front = new int[60];
		last = new int[60];
	}
	~Node() {
		delete[]front;
		delete[]last;
	}
};
bool isContain(int num, int* arry, int length)
{
	for (int i = 0; i < length; i++)
	{
		if (num == arry[i])
		{
			return true;
		}

	}
	return false;
}
int main()
{
	int vertices;
	int edges;
	cin >> vertices >> edges;
	Node* node = new Node[vertices + 5];
	bool f = true;
	int sign = 0;
	for (int i = 0; i < edges; i++)
	{
		int n1;
		int n2;
		cin >> n1 >> n2;
		if (n1 == n2)
		{
			f = false;
			sign = n1;
		}
		node[n1].num = n1;
		node[n1].exit++;
		node[n1].last[node[n1].last_num++] = n2;
		node[n2].num = n2;
		node[n2].enter++;
		node[n2].front[node[n2].front_num++] = n1;
	}
	if (f == false)
	{
		cout << "NO" << endl;
		cout << sign << "," << sign;
		return 0;
	}
	list<int> q1;
	for (int i = 1; i <= vertices; i++)
	{
		q1.push_back(node[i].num);
	}
	int mum = 0;
	int* arry = new int[vertices + 5];
	int total = 0;
	list<int>::iterator it = q1.begin();
	while (!q1.empty())
	{
		
		if (it == q1.end())
		{
			break;
		}
		else if (node[*it].enter == 0)
		{
			arry[total++] = *it;
			for (int j = 0; j < node[*it].last_num; j++)
			{
				node[node[*it].last[j]].enter -= 1;
			}
			q1.erase(it);
			it = q1.begin();
		}
		else
			it++;

	}
	if (it == q1.end() && q1.size() != 0)
	{
		it = q1.begin();
		cout << "NO" << endl;
		int init = *it;
		cout << init << ",";
		int temp = init;
		while (1)
		{
			bool f1 = isContain(init, node[temp].last, node[temp].last_num);
			bool f2 = isContain(*it, node[temp].last, node[temp].last_num);
			if (f1 == true)
			{
				cout << init;
				break;
			}
			else if (f2 == true && node[*it].exit != 0)
			{
				cout << *it << ",";
				temp = *it;
				if (q1.empty() == true)
				{
					cout << init;
					break;
				}
			}
			else
			{
				it++;
			}
		}
	}
	else
	{
		cout << "YES" << endl;
		for (int i = 0; i < total; i++)
		{
			if (i == total - 1)
			{
				cout << arry[i];
			}
			else
			{
				cout << arry[i] << ",";
			}
		}
	}
	delete[]arry;
	return 0;
}