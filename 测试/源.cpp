#include<iostream>
#include<cmath>
#include<fstream>
#include<regex>

#define PM 500
using namespace std;



int str_hash(string str,int n)
{
	long long sum = 0;
	int len = str.length();
	for (int i = 0; i < len; i++)
	{
		int temp = 1;
		int j = len - i - 1;
		if (j == 0)
			temp = str[i];
		else
		{
			while (j)
			{
				temp = temp * n;
				temp = temp % PM;
				j--;
			}
			temp = temp * str[i];
			temp = temp % PM;
		}
		sum += temp;
	}
	return sum % PM;
}

void insertStr(string arr[], string s, int h)
{
	if (arr[h] == "" || arr[h] == s)
	{
		arr[h] = s;
		return;
	}
	else
	{
		while (arr[h] != "" && arr[h] != s)
		{
			h++;
			if (h == PM)
				h = 0;
		}
		arr[h] = s;
		return;
	}
}

//������Ҵ���
int findStr(string arr[], string s, int h)
{
	int cmp = 0;
	while (arr[h] != s && arr[h]!="")
	{
		h++;
		cmp++;
		if (h == PM)
			h = 0;
	}
	cmp++;
	return cmp;
}

//��������±�
int findStr2(string arr[], string s, int h)
{
	int cmp = 0;
	while (arr[h] != s && arr[h]!="")
	{
		h++;
		cmp++;
		if (h == PM)
			h = 0;
	}
	if (arr[h] == "" || arr[h] != s)
	{
		cout << "���޴˴�" << endl;
		return -1;
	}
	cmp++;
	cout << "�±�Ϊ��" << h << endl;
	return h;
}

int cutAndHashWord(string str,int n)
{
	
	smatch sm;
	regex re("[^aeiou]+[aeiou][^aeiou](?=[^aeiou][aeiou])|[^aeiou]+[aeiou](?=[aeiou]|[^aeiou][aeiou])|[aeiou]+[^aeiou]+|[^aeiou][aeiou][^aeiou]+|[a-z]+|\'", regex::icase);
	string temp;
	string::const_iterator iterStart = str.begin();
	string::const_iterator iterEnd = str.end();
	long times = 1;
	int sum = 0;
	while (regex_search(iterStart, iterEnd, sm, re))
	{
		temp = sm[0];
		//cout << temp << " ";
		iterStart = sm[0].second;	//����������ʼλ��,����ʣ�µ��ַ���
		int a = str_hash(temp,31);
		sum += a * times % PM;
		times = times * n;
	}
	return sum % PM;
}


int main()
{
	ifstream input("sample.txt");
	string str[PM] = {};
	string hashLine1[PM] = {};
	string hashLine2[PM] = {};
	string hashLine3[PM] = {};
	long hashCmp1 = 0;
	long hashCmp2 = 0;
	long hashCmp3 = 0;
	int num = 0;
	string s;
	while (input >> s)
	{
		//cout << "����" << s << endl;
		int len = s.length();
		bool flag = 0;
		for (int i = 0; i < len; i++)
		{
			
			if (!((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z') || s[i] == '\''))
			{
				if (i == len - 1)
				{
					s = s.erase(i);
					break;
				}
				flag = 1;
				str[num + 1] = s.substr(i + 1, len - i + 1);
				str[num] = s.erase(i);
				//cout << "��� " << str[num] << endl;
				//cout << "��� " << str[num + 1] << endl;
				num += 2;
				break;
			}
			
		}
		if (!flag)
		{
			str[num] = s;
			//cout << "��� " << s;
			num++;
		}
		if (flag)
		{
			int h1 = str_hash(str[num - 2], 31);
			int h2 = str_hash(str[num - 2], 131);
			int hs1 = cutAndHashWord(str[num - 2], 31);
			//cout << "h1=" << h1 << "," << "h2=" << h2 << " ,hs1= " << hs1 <<endl;
			insertStr(hashLine1, str[num - 2], h1);
			insertStr(hashLine2, str[num - 2], h2);
			insertStr(hashLine3, str[num - 2], hs1);
		}
		
		int h3 = str_hash(str[num - 1], 31);
		int h4 = str_hash(str[num - 1], 131);
		int hs2 = cutAndHashWord(str[num - 1], 31);
		insertStr(hashLine1, str[num - 1], h3);
		insertStr(hashLine2, str[num - 1], h4);
		insertStr(hashLine3, str[num - 1], hs2);
		//cout << "h3=" << h3 << "," << "h4=" << h4 << endl;
	}


	//����
	for (int i = 0; i < num; i++)
	{
		hashCmp1 += findStr(hashLine1,str[i],str_hash(str[i], 31));
		hashCmp2 += findStr(hashLine2, str[i], str_hash(str[i], 131));
		hashCmp3 += findStr(hashLine3, str[i], cutAndHashWord(str[i], 31));
	}
	cout << "��������Ϊ " << num << endl;
	cout << "��ϣ�����洢����Ϊ " << PM << endl;
	cout << "��31Ϊ�׵Ĳ��Ҵ���Ϊ " << hashCmp1 << " ƽ�����ҳ���Ϊ " << hashCmp1/(double)num << endl;
	cout << "��131Ϊ�׵Ĳ��Ҵ���Ϊ " << hashCmp2 << " ƽ�����ҳ���Ϊ " << hashCmp2 / (double)num << endl;
	cout << "���ڲ��Ҵ���Ϊ " << hashCmp3 << " ƽ�����ҳ���Ϊ " << hashCmp3 / (double)num << endl;


	cout << endl << endl;

	//����article.txt�ļ��еĵ���
	string ttt;
	ifstream article("article.txt");
	while (article >> ttt)
	{
		cout << "����" << ttt << endl;
		findStr2(hashLine1, ttt, str_hash(ttt, 31));
		findStr2(hashLine2, ttt, str_hash(ttt, 131));
		findStr2(hashLine3, ttt, cutAndHashWord(ttt, 31));
		cout << endl;
	}
	return 0;
}