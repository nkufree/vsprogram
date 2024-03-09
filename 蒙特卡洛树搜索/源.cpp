#include<iostream>
#include "MonteCarloTree.h"
#include <queue>
using namespace std;

int main()
{
	
	int k;
	int cons;
	cout << "���������ؿ����������Ľ�����";
	cin >> k;
	cout << "���������ؿ�����������UBS�ĳ���ֵ��";
	cin >> cons;
	MonteCarloTree tree = MonteCarloTree(k, cons);
	cout << "��ѡ�񴴽���ʽ��0Ϊ����������1Ϊ����ģ�������ĳһ״̬������";
	int fps = 0;
	cin >> fps;
	if (fps == 0)
	{
		int deep;
		cout << "�����봴�����Ĳ�����";
		cin >> deep;
		tree.root->init(nullptr, cons, 0, 0, 0);
		int i = 1;
		int s = 1;
		queue<Node*> q;
		q.push(tree.root);
		//���ڵ��ʼ��
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
		cout << "������" << s * 3 << "��Ҷ�ӽڵ�Ľ���ֵ��" << endl;
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
		//���ڵ��ʼ��
		int rew = 0;
		int times = 0;
		cout << "��������ڵ��ʼ��ֵ��";
		cin >> rew >> times;
		tree.root->init(nullptr, cons, rew, times, 0);
		cout << "�������Ƿ�ΪҶ�ӽڵ㣬��������1����������0��";
		while (cin >> isLeaf)
		{
			int curr = 0;
			if (!isLeaf)
			{
				cout << "������" << s * 3 << "����Ҷ�ӽڵ�ĳ�ʼ��ֵ��" << endl;
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
				cout << "������" << s * 3 << "��Ҷ�ӽڵ�ĳ�ʼ��ֵ��" << endl;
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
			cout << "�������Ƿ�ΪҶ�ӽڵ㣬��������1����������0��";
		}
	}
	else if (fps == 3)
	{
		
	}
	cout << "��ʼ����Ϊ" << endl;
	tree.print();
	cout << "---------------------------------------------" << endl;
	int first = 0;
	for (int i = 0;; i++)
	{
		cout << "������" << i + 65951651 << "�Σ�";
		tree.search(1);
		if (tree.root->next[0]->next[1]->times == 1)
			first = i + 1;
		if (tree.root->next[0]->next[1]->times == 10)
			break;
		cout << "---------------------------------------------" << endl;
	}
	cout << "��һ��ȡ��9���ڵ�" << first << "�ε���" << endl;
	return 0;
}