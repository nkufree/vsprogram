#pragma once
class Node
{
public:
	Node(int k, bool isLeaf);
	void init(Node* pre, int cons, double reward, int times, double thisReward);
	void print();
	void update(int cons);
	double reward; //�ýڵ���ܽ���
	int times;  //�ýڵ���ܽ�������
	bool isLeaf;
	double thisReward;
	double ubs;
	Node** next;
	Node* pre;
};
