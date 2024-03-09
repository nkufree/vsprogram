#include <iostream>
using namespace std;

class ListNode
{
	
public:
	int val;
	ListNode* next;
	ListNode(int v, ListNode* n = nullptr) :val(v), next(n){}
	void insert(ListNode* p)
	{
		p->next = this->next;
		this->next = p;
	}
};

bool func(int a)
{
	if (a <= 1)
		return 0;
	else if (a == 2 || a == 3)
		return 1;
	for (int i = 2; i <= a / 2; i++)
	{
		if (a % i == 0)
			return false;
	}
	return 1;
}

int main()
{
	ListNode* head = new ListNode(0);
	ListNode* p = nullptr;
	int i = 1;
	while(i++ <= 100)
	{
		int a;
		cin >> a;
		if (func(a))
		{
			p = new ListNode(a);
			if (i == 2)
				head->next = p;
			else
			{
				ListNode* q = nullptr;
				q = head;
				while (q->next != nullptr)
				{
					if (q->val < a && q->next->val > a)
					{
						q->insert(p);
						break;
					}
					else if (q->val == a)
						break;
					q = q->next;
					if (q->next == nullptr && a != q->val)
					{
						q->insert(p);
						q = q->next;
					}
				} 
			}
		}
		else
			break;
	}
	ListNode* q = head->next;

	while (q != nullptr && q->next != nullptr)
	{
		cout << q->val << " ";
		q = q->next;
		
	}
	if(q != nullptr)
		cout << q->val;
	return 0;
}