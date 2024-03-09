#pragma once
#include "Node.h"
#include <vector>
using namespace std;
class MonteCarloTree
{
public:
	MonteCarloTree(int k,int cons);
	void setCons(int c);
	void search(bool show);
	void expand(Node* n);
	void print();
	void dfsUpdate(Node* n);
	int k; //���Ľ���
	int cons;
	vector<Node*> path;
	double reward;
	Node* root;

};

