#include "Node.h"
#include<iostream>
#include<cmath>
using namespace std;

Node::Node(int k, bool isLeaf = 0)
{
	if (isLeaf)
		next = nullptr;
	else
		next = new Node * [k];
	this->isLeaf = isLeaf;
}

void Node::init(Node* pre, int cons, double reward, int times, double thisReward = 0)
{
	this->reward = reward;
	this->times = times;
	this->thisReward = thisReward;
	this->pre = pre;
	this->update(cons);
	if (isLeaf)
		next = nullptr;
}

void Node::print()
{
	cout << reward << "/" << times << "\t";
}

void Node::update(int cons)
{
	if (times == 0 || this->pre == nullptr)
		return;
	ubs = reward / times + cons * sqrt(2 * log(pre->times) / times);
}


