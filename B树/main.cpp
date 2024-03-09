#include <iostream>
#include <cstdio>
#include "BTree.h"
#include "BTree.cpp"	
using namespace std;

bool cinFail() {
	if (!cin.fail())return 0;
	cout << "格式有误！" << endl;
	std::cin.clear();
	cin.ignore(1024, '\n');
	return 0;
}

int main() {
	cout << "请输入关键字个数及B树阶数：";
	int n, k;
	do {
		cin >> n >> k;
		if (cin.fail()) {
			cinFail();
			cout << "请重新输入关键字个数及B树阶数：";
		}
		else break;
	} while (1);

	BTree<int>*tree = new BTree<int>(k);
	cout << "以空格分隔输入的数据：" << endl;
	for (int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		if (cin.fail()) {
			cout << "格式有误!";
			delete tree;
			return 0;
		}
		tree->insert(x);
	}

	tree->printWholeTree();

	cout << "输入需要进行的操作,格式： 1.插入：I 整数 2.删除：D 整数 \n（E退出）\n";
	while (1) {
		char x;
		char y;
		int key;
		cin >> x;
		if (x == 'M')
		{
			cin >> y; 
			while (1)
			{
				char s;
				cin >> key;
				s = cin.get();
				if (y == 'I')
				{
					if (!tree->insert(key))cout << "有重复关键字\n";
				}
				else if (y == 'D')
				{
					if (!tree->erase(key))cout << "未找到相应的关键字\n";
				}
				if (s == ',')
					continue;
				else if (s == '#')
					break;
			}
		}
		else
		{
			if (cinFail())continue;
			if (x == 'E')break;
			cin >> key;
			if (cinFail())continue;
			else if (x == 'I') {
				if (!tree->insert(key))cout << "有重复关键字\n";
			}
			else if (x == 'D') {
				if (!tree->erase(key))cout << "未找到相应的关键字\n";
			}
			else {
				if (x != 'M')
				{
					cinFail();
					continue;
				}
			}
		}
		tree->printWholeTree();
	}
	delete tree;
	
	return 0;
}
