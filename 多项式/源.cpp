#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Node
{
public:
	Node(double c, int e) :coe(c), exp(e) {}
	double coe;
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
	void sortList()
	{
		int i, count = 0, num;
		Node* L = new Node(0,0);
		L->next = head;
		Node* p, * q, * tail2;
		p = L;
		while (p->next != NULL)
		{
			count++;
			p = p->next;
		}
		for (i = 0; i < count - 1; i++)
		{
			num = count - i - 1;
			q = L->next;
			p = q->next;
			tail2 = L;
			while (num--)
			{
				if (q->exp < p->exp)
				{
					q->next = p->next;
					p->next = q;
					tail2->next = p;
				}
				tail2 = tail2->next;
				q = tail2->next;
				p = q->next;
			}
		}
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
			double c = 0;
			i++;
			int flag = 1;
			if (str[i] == '-')
			{
				flag = -1;
				i++;
			}
			while (str[i] != ',' && str[i] != '.')
				c = c * 10 + str[i++] - '0';
			if (str[i] == '.')
			{
				int count0 = 0;
				i++;
				while (str[i] == '0')
				{
					count0++;
					i++;
				}
				double c2 = 0;
				while(str[i] != ',')
					c2 = c2 * 10 + str[i++] - '0';
				while (c2 > 1)
					c2 /= 10;
				while (count0 != 0)
				{
					c2 /= 10;
					count0--;
				}
				c += c2;
			}
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
				Node* p = new Node((double)c, e);
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
	while (p != nullptr || q != nullptr)
	{
		if (p == nullptr)
		{
			while (q != nullptr)
			{
				Node* n = new Node(q->coe, q->exp);
				polyOut->append(n);
				q = q->next;
			}
			
		}
		else if (q == nullptr)
		{
			while (p != nullptr)
			{
				Node* n = new Node(p->coe, p->exp);
				polyOut->append(n);
				p = p->next;
			}
		}
		else if (p->exp > q->exp)
		{
			double c = p->coe;
			int e = p->exp;
			Node* n = new Node(c, e);
			polyOut->append(n);
			p = p->next;
		}
		else if (p->exp < q->exp)
		{
			double c = q->coe;
			int e = q->exp;
			Node* n = new Node(c, e);
			polyOut->append(n);
			q = q->next;
		}
		else if (p->exp == q->exp)
		{
			double c = p->coe + q->coe;
			int e = p->exp;
			if (c != 0)
			{
				Node* n = new Node(c, e);
				polyOut->append(n);
				p = p->next;
				q = q->next;
			}
			else if (c == 0)
			{
				p = p->next;
				q = q->next;
			}
		}
	}
	return polyOut;
}

List* PolySub(List* list1, List* list2)
{
	List* polyOut = new List();
	Node* p = list1->head;
	Node* q = list2->head;
	while (p != nullptr || q != nullptr)
	{
		if (p == nullptr)
		{
			while (q != nullptr)
			{
				Node* n = new Node(q->coe, q->exp);
				polyOut->append(n);
				q = q->next;
			}

		}
		else if (q == nullptr)
		{
			while (p != nullptr)
			{
				Node* n = new Node(p->coe, p->exp);
				polyOut->append(n);
				p = p->next;
			}
		}
		else if (p->exp > q->exp)
		{
			double c = p->coe;
			int e = p->exp;
			Node* n = new Node(c, e);
			polyOut->append(n);
			p = p->next;
		}
		else if (p->exp < q->exp)
		{
			double c = -q->coe;
			int e = q->exp;
			Node* n = new Node(c, e);
			polyOut->append(n);
			q = q->next;
		}
		else if (p->exp == q->exp)
		{
			double c = p->coe - q->coe;
			int e = p->exp;
			if (c != 0)
			{
				Node* n = new Node(c, e);
				polyOut->append(n);
				p = p->next;
				q = q->next;
			}
			else if (c == 0)
			{
				p = p->next;
				q = q->next;
			}
		}
	}
	return polyOut;
}

List* PolyDiff(List* list1)
{
	List* polyOut = new List();
	Node* p = list1->head;
	while (p != nullptr)
	{
		double c = p->coe * p->exp;
		int e = p->exp - 1;
		if (c != 0)
		{
			Node* n = new Node(c, e);
			polyOut->append(n);
		}
		p = p->next;
	}
	return polyOut;
}

List* PolyMul(List* list1, List* list2)
{
	List* polyOut = new List();
	Node* p = list1->head;
	Node* q = list2->head;
	for (int i = 0; q != nullptr; i++)
	{
		List* temp = new List();
		while (p != nullptr)
		{
			Node* n = new Node(p->coe * q->coe, p->exp + q->exp);
			temp->append(n);
			p = p->next;
		}
		p = list1->head;
		if (i == 0)
			polyOut = temp;
		else
			polyOut = PolyAnd(polyOut, temp);

		q = q->next;
	}
	return polyOut;
}

List* PolyDiv(List*& list1, List* list2)
{
	List* polyOut = new List();
	Node* p = list1->head;
	Node* q = list2->head;
	List* t = nullptr;
	List* modOut = nullptr;
	while (p->exp >= q->exp)
	{
		List* temp = new List();
		double c = p->coe / q->coe;
		int e = p->exp - q->exp;
		Node* n = new Node(c, e);
		polyOut->append(n);
		temp->append(n);
		t = PolyMul(temp, list2);
		modOut = PolySub(list1, t);
		p = modOut->head;
		q = list2->head;
		list1 = modOut;
		if (p == nullptr)
			break;
	}
	return polyOut;
}

void outPut(ofstream& outPoly, List* PolyOut)
{
	Node* n = PolyOut->head;
	while (n != nullptr)
	{
		if (n == PolyOut->head)
		{
			if (n->coe == 1)
				outPoly << "x" << n->exp;
			else
				outPoly << n->coe << "x" << n->exp;
		}
		else
		{
			if (n->exp != 0)
			{
				if (n->coe == 1)
					outPoly << '+' << "x" << n->exp;
				else if (n->coe > 0)
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
		n = n->next;
	}
	return;
}

void main()
{
	ifstream inputdata("inputfile.txt");
	string str1, str2, str3;
	inputdata >> str1 >> str2 >> str3;
	inputdata.close();
	List* list1 = new List();
	List* list2 = new List();
	if (str3 == "")
	{
		buildList(str1, list1);
		str3 = str2;
	}
	else
	{
		buildList(str1, list1);
		list1->sortList();
		list1->print();
		cout << "------------------------" << endl;
		buildList(str2, list2);
		//list2->sortList();
		list2->print();
		cout << "-----------------------" << endl;
	}
	char s[5] = {};
	int i = 0;
	while (str3[i] != '(')
	{
		s[i] = str3[i];
		i++;
	}
	string str4 = s;
	List* PolyOut = nullptr;
	if (str4 == "AND")
		PolyOut = PolyAnd(list1, list2);
	else if (str4 == "SUB")
		PolyOut = PolySub(list1, list2);
	else if (str4 == "DIFF")
		PolyOut = PolyDiff(list1);
	else if (str4 == "MUL")
		PolyOut = PolyMul(list1, list2);
	else if (str4 == "DIV")
		PolyOut = PolyDiv(list1, list2);
	ofstream outPoly("outputfile.txt");
	outPut(outPoly, PolyOut);
	if (str4 == "DIV")
	{
		outPoly << endl;
		outPut(outPoly, list1);
	}
	outPoly.close();
	return;
}