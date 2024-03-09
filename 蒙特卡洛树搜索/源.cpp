#include<iostream>
#include "MonteCarloTree.h"
#include <queue>
using namespace std;

int main()
{
	
	int k;
	int cons;
	cout << "请输入蒙特卡洛树搜索的阶数：";
	cin >> k;
	cout << "请输入蒙特卡洛树搜索中UBS的常数值：";
	cin >> cons;
	MonteCarloTree tree = MonteCarloTree(k, cons);
	cout << "请选择创建方式：0为创建空树，1为创建模拟过程中某一状态的树：";
	int fps = 0;
	cin >> fps;
	if (fps == 0)
	{
		int deep;
		cout << "请输入创建树的层数：";
		cin >> deep;
		tree.root->init(nullptr, cons, 0, 0, 0);
		int i = 1;
		int s = 1;
		queue<Node*> q;
		q.push(tree.root);
		//根节点初始化
		tree.root->init(nullptr, 0, 0, 0, 0);
		int curr = 0;
		while (i < deep - 1)
		{
			curr = 0;
			for (; curr < s; curr++)
			{
				Node* n = q.front();
				q.pop();
				for (int i = 0; i < k; i++)
				{
					n->next[i] = new Node(k, 0);
					n->next[i]->init(n, cons, 0, 0, 0);
					q.push(n->next[i]);
				}
			}
			s *= 3;
			i++;
		}
		curr = 0;
		cout << "请输入" << s * 3 << "个叶子节点的奖励值：" << endl;
		for (; curr < s; curr++)
		{
			Node* n = q.front();
			q.pop();
			int thisRew = 0;
			for (int i = 0; i < k; i++)
			{
				cin >> thisRew;
				n->next[i] = new Node(k, 0);
				n->next[i]->isLeaf = 1;
				n->next[i]->init(n, cons, 0, 0, thisRew);
			}
		}
	}
	else if (fps == 1)
	{
		int isLeaf;
		int s = 1;
		queue<Node*> q;
		q.push(tree.root);
		//根节点初始化
		int rew = 0;
		int times = 0;
		cout << "请输入根节点初始化值：";
		cin >> rew >> times;
		tree.root->init(nullptr, cons, rew, times, 0);
		cout << "请输入是否为叶子节点，若是输入1，若否输入0：";
		while (cin >> isLeaf)
		{
			int curr = 0;
			if (!isLeaf)
			{
				cout << "请输入" << s * 3 << "个非叶子节点的初始化值：" << endl;
				for (; curr < s; curr++)
				{
					Node* n = q.front();
					q.pop();
					for (int i = 0; i < k; i++)
					{
						cin >> rew >> times;
						n->next[i] = new Node(k, 0);
						n->next[i]->init(n, cons, rew, times, 0);
						q.push(n->next[i]);
					}
				}
				s *= 3;
			}
			else
			{
				cout << "请输入" << s * 3 << "个叶子节点的初始化值：" << endl;
				for (; curr < s; curr++)
				{
					Node* n = q.front();
					q.pop();
					int thisRew = 0;
					for (int i = 0; i < k; i++)
					{
						cin >> rew >> times >> thisRew;
						n->next[i] = new Node(k, 0);
						n->next[i]->isLeaf = 1;
						n->next[i]->init(n, cons, rew, times, thisRew);
					}
				}
				break;
			}
			cout << "请输入是否为叶子节点，若是输入1，若否输入0：";
		}
	}
	else if (fps == 3)
	{
		
	}
	cout << "初始树形为" << endl;
	tree.print();
	cout << "---------------------------------------------" << endl;
	int first = 0;
	for (int i = 0;; i++)
	{
		cout << "迭代第" << i + 65951651 << "次，";
		tree.search(1);
		if (tree.root->next[0]->next[1]->times == 1)
			first = i + 1;
		if (tree.root->next[0]->next[1]->times == 10)
			break;
		cout << "---------------------------------------------" << endl;
	}
	cout << "第一次取到9是在第" << first << "次迭代" << endl;
	return 0;
}