#include <iostream>
#include <stack>
using namespace std;
class Node
{
public:
	int num;
	Node* next;
};
void print(Node* p)
{
	if (p != nullptr)
	{
		print(p->next);
		cout << p->num << endl;
	}
}

void hsort(stack<int>& s, int num)
{
	if (s.empty())
		s.push(num);
	else
	{
		int num2 = s.top();
		s.pop();
		if (num2 > num)
		{
			int temp = num2;
			num2 = num;
			num = temp;
		}
		hsort(s, num);
		s.push(num2);
	}
}

void sort(stack<int>& s)
{
	for (int i = 0; i < s.size(); i++)
	{
		int num = s.top();
		s.pop();
		hsort(s, num);
	}
	return;
}

void main()
{
	stack<int> s;
	s.push(1);
	s.push(4);
	s.push(9);
	s.push(3);
	s.push(5);
	s.push(10);
	s.push(6);
	s.push(0);
	sort(s);
	for (int i = 0; !s.empty(); i++)
	{
		cout << s.top() << " ";
		s.pop();
	}
	return;

}