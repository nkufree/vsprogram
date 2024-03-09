#include <iostream>
using namespace std;

class Student
{
public:
	int num;
	int score;
	Student() {}

};

void max(Student* stu)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 3; j > 3 - i; j--)
		{  
			if ((stu + j)->score > (stu + j - 1)->score)
			{
				int s;
				s = (stu + j)->score;
				(stu + j)->score = (stu + j - 1)->score;
				(stu + j - 1)->score = s;
				s = (stu + j)->num;
				(stu + j)->num = (stu + j - 1)->num;
				(stu + j - 1)->num = s;
			}
			else if ((stu + j)->score == (stu + j - 1)->score && (stu + j)->num < (stu + j - 1)->num)
			{
				int s;
				s = (stu + j)->score;
				(stu + j)->score = (stu + j - 1)->score;
				(stu + j - 1)->score = s;
				s = (stu + j)->num;
				(stu + j)->num = (stu + j - 1)->num;
				(stu + j - 1)->num = s;
			}
		}
	}
}

int main()
{
	Student st[4]{};
	for (int i = 0; i < 4; i++)
	{
		cin >> st[i].num >> st[i].score;
	}
	max(st);
	for (int i = 0; i < 4; i++)
	{
		if (st[i].score == st[0].score)
			cout << st[i].num << " " << st[i].score << endl;
	}
}