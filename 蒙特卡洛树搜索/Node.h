#pragma once
class Node
{
public:
	Node(int k, bool isLeaf);
	void init(Node* pre, int cons, double reward, int times, double thisReward);
	void print();
	void update(int cons);
	double reward; //该节点的总奖励
	int times;  //该节点的总奖励次数
	bool isLeaf;
	double thisReward;
	double ubs;
	Node** next;
	Node* pre;
};
