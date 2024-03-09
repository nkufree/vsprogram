#include "MonteCarloTree.h"
#include <queue>
#include <iostream>
using namespace std;

MonteCarloTree::MonteCarloTree(int k, int cons = 1)
{
	this->k = k;
	this->cons = cons;
	Node* n = new Node(k,0);
	root = n;
	reward = 0;
}

void MonteCarloTree::setCons(int c)
{
	cons = c;
	dfsUpdate(root);
}

void MonteCarloTree::dfsUpdate(Node* n)
{
	n->update(cons);
	for (int i = 0; i < this->k; i++)
		dfsUpdate(n->next[i]);
}

void MonteCarloTree::search(bool show = 1)
{
	path.clear();
	path.push_back(root);
	expand(root);
	for (int i = 0; i < path.size(); i++)
	{
		path[i]->reward += reward;
		path[i]->times++;
		path[i]->update(cons);
	}
	if(show)
		this->print();
}

void MonteCarloTree::expand(Node* n)
{
	if (n->isLeaf)
	{
		cout << "选择节点的奖励为" << n->thisReward << endl;;
		reward = n->thisReward;
		return;
	}
	double max = 0;
	int index = 0;
	for (int i = 0; i < k; i++)
	{
		if (n->next[i]->times == 0)
		{
			Node* temp = n->next[i];
			path.push_back(temp);
			while (!temp->isLeaf)
				temp = temp->next[0];
			expand(temp);
			return;
			
		}
		if (n->next[i]->ubs > max)
		{
			max = n->next[i]->ubs;
			index = i;
		}
	}
	path.push_back(n->next[index]);
	expand(n->next[index]);
}

void MonteCarloTree::print()
{
	queue<Node*> q;
	q.push(root);
	int flag = 0;
	int s = 1;
	int co = 0;
	while (!q.empty())
	{
		Node* cur = q.front();
		q.pop();
		cur->print();
		if (!cur->isLeaf)
			for (int i = 0; i < k; i++)
				q.push(cur->next[i]);
		co++;
		if (co == s)
		{
			s *= 3;
			co = 0;
			cout << endl;
		}
	}
	cout << endl;
}

