#include <iostream>
#include <cstdio>
#include "BTree.h"
#include "BTree.cpp"	
using namespace std;

bool cinFail() {
	if (!cin.fail())return 0;
	cout << "��ʽ����" << endl;
	std::cin.clear();
	cin.ignore(1024, '\n');
	return 0;
}

int main() {
	cout << "������ؼ��ָ�����B��������";
	int n, k;
	do {
		cin >> n >> k;
		if (cin.fail()) {
			cinFail();
			cout << "����������ؼ��ָ�����B��������";
		}
		else break;
	} while (1);

	BTree<int>*tree = new BTree<int>(k);
	cout << "�Կո�ָ���������ݣ�" << endl;
	for (int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		if (cin.fail()) {
			cout << "��ʽ����!";
			delete tree;
			return 0;
		}
		tree->insert(x);
	}

	tree->printWholeTree();

	cout << "������Ҫ���еĲ���,��ʽ�� 1.���룺I ���� 2.ɾ����D ���� \n��E�˳���\n";
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
					if (!tree->insert(key))cout << "���ظ��ؼ���\n";
				}
				else if (y == 'D')
				{
					if (!tree->erase(key))cout << "δ�ҵ���Ӧ�Ĺؼ���\n";
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
				if (!tree->insert(key))cout << "���ظ��ؼ���\n";
			}
			else if (x == 'D') {
				if (!tree->erase(key))cout << "δ�ҵ���Ӧ�Ĺؼ���\n";
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
