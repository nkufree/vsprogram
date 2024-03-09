#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Node
{
public:
	Node(int c, int e):coe(c),exp(e){}
	int coe;
	int exp;
	Node* next;
};

class List
{
public:
	List() {}
	Node* head;
	Node* tail;
	void append(Node* p)
	{
		if (tail == nullptr)
		{
			head = p;
			tail = p;
			return;
		}
		tail->next = p;
		tail = p;
		return;
	}
	void print()
	{
		Node* t = head;
		while (t != nullptr)
		{
			cout << t->coe << " " << t->exp << endl;
			t = t->next;
		}
		return;

	}
};

void buildList(string str, List* list)
{
	int i = 0;
	while (i < str.length())
	{
		if (str[i] == '(')
		{
			int c = 0;
			i++;
			int flag = 1;
			if (str[i] == '-')
			{
				flag = -1;
				i++;
			}
			while (str[i] != ',')
				c = c * 10 + str[i++] - '0';
			c = c * flag;
			int e = 0;
			i++;
			while (str[i] != ')')
				e = e * 10 + str[i++] - '0';
			i++;
			if (c == 0 && e == 0)
				break;
			else
			{
				Node* p = new Node(c, e);
				list->append(p);
			}
		}
	}
}

List* PolyAnd(List* list1, List* list2)
{
	List* polyOut = new List();
	Node* p = list1->head;
	Node* q = list2->head;
	while (p != nullptr && q != nullptr)
	{
		if (p == nullptr)
		{
			while (q != nullptr)
			{
				Node* n = new Node(q->coe, q->exp);
				q = q->next;
			}
		}
		else if (q == nullptr)
		{
			while (p != nullptr)
			{
				Node* n = new Node(p->coe, p->exp);
				p = p->next;
			}
		}
		else if (p->exp > q->exp)
		{
			int c = p->coe, e = p->exp;
			Node* n = new Node(c, e);
			polyOut->append(n);
			p = p->next;
		}
		else if (p->exp < q->exp)
		{
			int c = q->coe, e = q->exp;
			Node* n = new Node(c, e);
			polyOut->append(n);
			q = q->next;
		}
		else if (p->exp == q->exp)
		{
			int c = p->coe + q->exp , e = p->exp + q->exp;
			if (c != 0)
			{
				Node* n = new Node(c, e);
				polyOut->append(n);
				p = p->next;
				q = q->next;
			}
		}
	}
	polyOut->print();
	return polyOut;
}

List* PolySub(List* list1, List* list2)
{
	List* polyOut = new List();
	int c = 0, e = 0;
	return polyOut;
}

List* PolyDiff(List* list1, List* list2)
{
	List* polyOut = new List();
	int c = 0, e = 0;
	return polyOut;
}

List* PolyMul(List* list1, List* list2)
{
	List* polyOut = new List();
	int c = 0, e = 0;
	return polyOut;
}

List* PolyDiv(List* list1, List* list2)
{
	List* polyOut = new List();
	int c = 0, e = 0;
	return polyOut;
}

void main()
{
	ifstream inputdata("inputfile.txt");
	string str1, str2, str3;
	inputdata >> str1 >> str2 >> str3;
	inputdata.close();
	List* list1 = new List();
	List* list2 = new List();
	buildList(str1, list1);
	list1->print();
	cout << "------------------------" << endl;
	buildList(str2, list2);
	list2->print();
	cout << "-----------------------" << endl;
	char s[5] = {};
	int i = 0;
	while (str3[i] != '(')
	{
		s[i] = str3[i];
		i++;
	}
	string str4 = s;
	List* PolyOut;
	if (str4 == "AND")
		PolyOut = PolyAnd(list1, list2);
	else if(str4 == "SUB")
		PolyOut = PolySub(list1, list2);
	else if (str4 == "DIFF")
		PolyOut = PolyDiff(list1, list2);
	else if (str4 == "MUL")
		PolyOut = PolyMul(list1, list2);
	else if (str4 == "DIV")
		PolyOut = PolyDiv(list1, list2);
	PolyOut->print();
	ofstream outPoly("outputfile.txt");
	Node* n = PolyOut->head;
	while (n != nullptr)
	{
		if (n == PolyOut->head)
			outPoly << n->coe << "x" << n->exp;
		else
		{
			if (n->exp != 0)
			{
				if (n->coe > 0)
					outPoly << '+' << n->coe << "x" << n->exp;
				else
					outPoly << n->coe << "x" << n->exp;
			}
			else if (n->exp == 0)
			{
				if (n->coe > 0)
					outPoly << '+' << n->coe;
				else
					outPoly << n->coe;
			}
		}
	}
	outPoly.close();
	return;

}