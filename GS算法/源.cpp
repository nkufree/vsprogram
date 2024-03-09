#include<iostream>
#include<vector>
#include<queue>
using namespace std;

void inputIdea(vector<vector<int>> &in,int size)
{
	for (int i = 0; i < size; i++)
	{
		vector<int> temp;
		for (int j = 0; j < size; j++)
		{
			int k;
			cin >> k;
			temp.push_back(k - 1);

		}
		in.push_back(temp);
	}
	return;
}

bool change(vector<int> woman, int old, int now)
{
	for (int i = 0; i < woman.size(); i++)
	{
		if (woman[i] == old)
			return false;
		else if (woman[i] == now)
			return true;
	}
}


int* GSmatch(vector<vector<int>> man, vector<vector<int>> woman)
{
	//cout << endl;
	int n = man.size();
	int* matchMan = new int[n];
	int* matchWoman = new int[n];
	for (int i = 0; i < n; i++)
		matchWoman[i] = -1;
	queue<int> singleMan;
	for (int i = 0; i < n; i++)
		singleMan.push(i);
	while (!singleMan.empty())
	{
		int a = singleMan.front();//Ŀǰ����ƥ���man
		singleMan.pop();
		vector<int>& b = man[a];
		for (int i = 0; i < n; i++)
		{
			int j = b[i];//Ŀǰ����ƥ���woman
			if (matchWoman[j] == -1)
			{
				matchMan[a] = j;
				matchWoman[j] = a;
				//cout << "��ʿ" << a+1 << "ƥ��Ůʿ" << j+1 << "�ɹ�" << endl;
				break;
			}
			else if (matchWoman[j] != -1 && change(woman[j], matchWoman[j], a))
			{
				matchMan[matchWoman[j]] = -1;
				//cout << "ȡ����ʿ" << matchWoman[j]+1 << "��Ůʿ" << j+1 << "�����" << endl;
				singleMan.push(matchWoman[j]);
				matchWoman[j] = a;
				matchMan[a] = j;
				//cout << "��ʿ" << a+1 << "ƥ��Ůʿ" << j+1 << "�ɹ�" << endl;
				break;
			}
			else
			{
				continue;
			}
		}
	}
	//cout << endl;
	delete matchWoman;
	return matchMan;
}



int main()
{
	int n;
	cin >> n;
	vector<vector<int>> man;
	vector<vector<int>> woman;
	inputIdea(man,n);
	inputIdea(woman,n);
	int* matchMan = GSmatch(man, woman);
	for (int i = 0; i < n; i++)
		cout << matchMan[i] + 1 << " ";

	return 0;
}