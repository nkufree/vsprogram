#include<iostream>
#include<iomanip>
#include<queue>
#include<fstream>
#include<Windows.h>

using namespace std;
long len = 0;
long total = 0;
/*
class Node
{
public:
	Node(int w) :weight(w) { m = 0; left = nullptr; right = nullptr; }
	Node(int w, int s) :weight(w), m(s) { left = nullptr; right = nullptr; }
	int m;
	int weight;
	Node* left;
	Node* right;
};

//求编码
void tcode(Node* n, int dep)
{
	if (n->left == nullptr && n->right == nullptr)
	{
		if (n->m)
		{
			len += dep * n->weight;
		}
		//cout << codeList[n->m - 1].s << " " << codeList[n->m - 1].code << endl;
		return;
	}
	if (n->left != nullptr)
		tcode(n->left, dep+1);
	if (n->right != nullptr)
		tcode(n->right, dep+1);
}
class cmp {
public:
	bool operator()(Node* & a, Node* & b) {
		return a->weight > b->weight;
	}
};

int main()
{
	int flag = 0;
	int count;
	priority_queue<Node*, vector<Node*>, cmp> q;
	
	cin >> count;
	for (int i = 0; i < count; i++)
	{
		int fr;
		cin >> fr;
		Node* p = new Node(fr, i+1);
		q.push(p);
		total += fr;
	}
	//构造Huffman树
	Node* root = nullptr;
	while (q.size() != 1)
	{
		Node* pl = q.top();
		q.pop();
		Node* pr = q.top();
		q.pop();
		Node* p = new Node(pl->weight + pr->weight);
		p->left = pl;
		p->right = pr;
		q.push(p);
	}
	root = q.top();
	tcode(root,0);
	cout << fixed << setprecision(2) << len * 1.0 / total;
	cout << endl;
	QueryPerformanceCounter((LARGE_INTEGER*)&time1);
	cout  << (time1 - time0) * 1000.0 / freq << "ms" << endl;
	return 0;
}*/
int main()
{
	int flag = 0;
	int count;
	priority_queue<int,vector<int>,greater<int>> q;

	cin >> count;
	for (int i = 0; i < count; i++)
	{
		int fr;
		cin >> fr;
		q.push(fr);
		total += fr;
	}
	//构造Huffman树
	while (q.size() != 1)
	{
		int temp = 0;
		temp = q.top();
		q.pop();
		temp += q.top();
		q.pop();
		q.push(temp);
		len += temp;
	}
	cout << fixed << setprecision(2) << len * 1.0 / total;
	return 0;
}