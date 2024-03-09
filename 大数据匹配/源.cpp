#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<ctime>

#define MAXSIZE 135000
#define ASIZE 40000

using namespace std;


class Person
{
public:
	int _id;
	vector<string> _v;
	Person() {}
	Person(vector<string> v)
	{
		_id = atoi(v[0].c_str());
		_v = v;
	}
};

bool cmpp(Person p1, Person p2)
{
	return p1._v[4] < p2._v[4];
}

bool cmpi(vector<Person*> v1, vector<Person*> v2)
{
	return v1[0]->_id < v2[0]->_id;
}

bool cmpvp(Person* p1, Person* p2)
{
	return p1->_id < p2->_id;
}

int min3(int a, int b, int c) {
	a = a < b ? a : b;
	return a < c ? a : c;
}

int LevenshteinDP(string s, string t) {
	//levenshtein����Ķ�̬�滮ʵ��
	int dp[20][20] = {};
	for (int i = 0; i <= s.length(); i++)dp[i][0] = i;
	for (int j = 1; j <= t.length(); j++)dp[0][j] = j;
	for (int j = 0; j < t.length(); j++) {
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == t[j])dp[i + 1][j + 1] = dp[i][j];
			else dp[i + 1][j + 1] = min3(dp[i][j + 1] + 1, dp[i + 1][j] + 1, dp[i][j] + 1);
		}
	}
	return dp[s.length()][t.length()];
}

void main()
{
	char* oneLine = new char[1000];
	fstream csvtest("test2.csv");
	vector<Person> person;
	//Person* person2[ASIZE] = {};
	int count = 0;
	int count2 = 0;
	vector<vector<Person*>> index;
	time_t t0 = time(0);
	while (csvtest.getline(oneLine, 1000))
	{
		string str = oneLine;
		size_t pos = str.find(',');
		vector<string> str_results;
		while (pos != str.npos)
		{
			string temp = str.substr(0, pos);
			str_results.push_back(temp);
			str = str.substr(pos + 1, str.size());
			pos = str.find(',');
		}
		/*for (auto str_ : str_results)
		{
			cout << str_ << endl;
		}*/
		Person temp(str_results);
		person.push_back(temp);
		count++;
		//cout << count << endl;
	}
	count = 0;

	time_t t1 = time(0);
	cout << "¼�����,��ʱ" << difftime(t1, t0) << "��" << endl;
	csvtest.close();

	/*
	ifstream outtxt("out.txt");
	ofstream acsv("a.csv");
	while (outtxt.getline(oneLine, 1000))
	{
		string str = oneLine;
		size_t pos = str.find(',');
		string str_results;
		if (pos != str.npos)
		{
			str_results = oneLine;
		}
		else
		{
			str_results = str.substr(0, pos);
		}
		for (int i = 0; i < person[atoi(str_results.c_str())]._v.size(); i++)
		{
			acsv << person[atoi(str_results.c_str())]._v[i] << ",";
		}
		acsv << endl;
	}
	*/

	/*
	//��out.txt�ж�ȡ���ݣ�ȡÿ�е�һ��
	ifstream outtxt("out.txt");
	while (outtxt.getline(oneLine, 1000))
	{
		string str = oneLine;
		size_t pos = str.find(',');
		vector<string> str_results;
		vector<Person*> vp;
		while (pos != str.npos)
		{
			string temp = str.substr(0, pos);
			str_results.push_back(temp);
			str = str.substr(pos + 1, str.size());
			pos = str.find(',');
		}
		str_results.push_back(str.substr(0, pos));
		for (int i = 0; i < str_results.size(); i++)
		{
			vp.push_back(&person[atoi(str_results[i].c_str())]);
		}
		index.push_back(vp);
	}
	outtxt.close();
	*/
	/*
	int clearcount = 0;
	vector<vector<Person*>>::iterator it0 = index.end() - 1;
	int total = index.size();
	for (int i = index.size() - 1; i > 0; i--)
	{
		bool flag = false;
		for (int j = 0; j < i; j++)
		{
			vector<string>& v1 = index[i][0]->_v;
			vector<string>& v2 = index[j][0]->_v;
			if ((v1[2] == v2[2] || (v1[2].length() == v2[2].length() && LevenshteinDP(v1[2], v2[2]) < 3))
				&& v1[4] == v2[4]
				&& (v1[3] == v2[3] || (v1[3][0] == v2[3][0] && (v1[3].length() == 1 || v2[3].length() == 1 || LevenshteinDP(v1[3], v2[3]) < 4)))
				&& (v1[5] == v2[5] || (v1[5][0] == v2[5][0] && (v1[5].length() == 1 || v2[5].length() == 1 || LevenshteinDP(v1[5], v2[5]) < 4))))
			{
				total--;
				it0--;
				flag = true;
				clearcount++;
				cout << "�����" << index[i][0]->_id << ",�ӵ���" << index[j][0]->_id << "�������" << clearcount <<endl;
				index[j].insert(index[j].end(), index[i].begin(), index[i].end());
				sort(index[j].begin(), index[j].end(), cmpvp);
				index.erase(it0 + 1);

				break;
			}
		}
		if (!flag)
			it0--;
	}


	ofstream out("out.txt");
	for (int i = 0; i < index.size(); i++)
	{
		vector<Person*>& vp = index[i];
		if (vp.size() == 1)
		{
			out << vp[0]->_id << endl;
		}
		else
		{
			for (int j = 0; j < vp.size() - 1; j++)
			{
				out << vp[j]->_id << ",";
			}
			out << vp[vp.size() - 1]->_id << endl;
		}
	}

	out.close();*/

	//�����м��������򣬵�һ��ƥ��ֻƥ���м�������ͬ����Ϣ
	stable_sort(person.begin(), person.end(), cmpp);
	time_t t2 = time(0);
	cout << "������ɣ���ʱ" << difftime(t2, t1) << "��" << endl;


	//�Ƚ����������еȻ�����ͬ�ķ���һ����С����ƥ��ʱ��
	int left = 0;
	string mName = person[0]._v[4];
	while (count != person.size())
	{
		//cout << oneLine << endl;
		Person* temp = &person[count];
		//person[count] = temp;
		if (count2 == 0 || temp->_v[4] != mName)
		{
			//person2[count2] = temp;
			vector<Person*> vtemp;
			vtemp.push_back(temp);
			index.push_back(vtemp);
			count2++;
			mName = temp->_v[4];
			left = count2;
		}
		else
		{
			bool flag = false;
			for (int i = left; i < count2; i++)
			{

				vector<string> v1 = temp->_v;
				vector<Person*>& v2 = index[i];
				int a = 0;
				vector<string> v3 = v2[0]->_v;
				for (int k = 2; k < 12; k++)
				{
					if (v3[k] == v1[k])
						a++;
				}
				if (a >= 6)
				{
					flag = true;
					v2.push_back(temp);
					break;
				}
			}
			if (!flag)
			{
				vector<Person*> vtemp;
				vtemp.push_back(temp);
				index.push_back(vtemp);
				count2++;
			}

		}
		count++;
		cout << count << ";" << count2 << endl;
	}
	cout << "end" << endl;

	//����ÿ����С������
	sort(index.begin(), index.end(), cmpi);
	cout << "�������" << endl;

	time_t t3 = time(0);
	cout << "��һ��ƥ�䡢������ɣ���ʱ" << difftime(t3, t2) << "��" << endl;
	cout << "����" << index.size() << "����ͬ����" << endl;

	//���м����ֲ�ͬ�Ľ���ƥ��
	vector<vector<Person*>>::iterator it = index.end()-1;
	int total = index.size();
	for (int i = index.size() - 1; i > 0; i--)
	{
		bool flag = false;//��Ϊ�Ƿ�ƥ�䵽�ı�־
		for (int j = 0; j< i; j++)
		{
			vector<string> &v1 = index[i][0]->_v;
			vector<string> &v2 = index[j][0]->_v;
			if (v1[4] == v2[4])
				continue;
			int a = 0;
			for (int k = 2; k < 12; k++)
			{
				if (v2[k] == v1[k])
					a++;
			}
			if (a >= 6)
			{
				total--;
				it--;
				flag = true;
				cout << "�����" << index[i][0]->_id << ",�ӵ���" << index[j][0]->_id << endl;
				index[j].insert(index[j].end(), index[i].begin(), index[i].end());
				sort(index[j].begin(), index[j].end(), cmpvp);
				index.erase(it+1);

				break;
			}
		}
		if(!flag)
			it--;
	}
	time_t t4 = time(0);
	cout << "�ڶ���ƥ����ɣ���ʱ" << difftime(t4, t3) << "��" << endl;
	cout << "����" << index.size() << "����ͬ����" << endl;
	//���籣�Ž���ƥ��
	int clearcount = 0;
	vector<vector<Person*>>::iterator it0 = index.end() - 1;
	total = index.size();
	for (int i = index.size() - 1; i > 0; i--)
	{
		bool flag = false;//��Ϊ�Ƿ�ƥ�䵽�ı�־
		for (int j = 0; j < i; j++)
		{
			vector<string>& v1 = index[i][0]->_v;
			vector<string>& v2 = index[j][0]->_v;
			//��������������һ����ĸ��Ϊ��д
			if ((v1[2] == v2[2] || (v1[2].length() == v2[2].length() && LevenshteinDP(v1[2], v2[2]) < 3))
				&& (v1[3] == v2[3] || ((v1[3][0] == v2[3][0] && (v1[3].length() == 1 || v2[3].length() == 1)) || LevenshteinDP(v1[3], v2[3]) < 4))
				&& (v1[5] == v2[5] || ((v1[5][0] == v2[5][0] && (v1[5].length() == 1 || v2[5].length() == 1)) || LevenshteinDP(v1[5], v2[5]) < 4)))
			{
				total--;
				it0--;
				flag = true;
				clearcount++;
				cout << "�����" << index[i][0]->_id << ",�ӵ���" << index[j][0]->_id << "�������" << clearcount << endl;
				index[j].insert(index[j].end(), index[i].begin(), index[i].end());
				sort(index[j].begin(), index[j].end(), cmpvp);
				index.erase(it0 + 1);

				break;
			}
		}
		if (!flag)
			it0--;
	}

	time_t t5 = time(0);
	cout << "������ƥ����ɣ���ʱ" << difftime(t5,t4) << "��" << endl;
	cout << "����" << index.size() << "����ͬ����" << endl;
	ofstream out("out.txt");
	for (int i = 0; i < index.size(); i++)
	{
		vector<Person*>& vp = index[i];
		if (vp.size() == 1)
		{
			out << vp[0]->_id << endl;
		}
		else
		{
			for (int j = 0; j < vp.size() - 1; j++)
			{
				out << vp[j]->_id << ",";
			}
			out << vp[vp.size() - 1]->_id << endl;
		}
	}




	return;
}