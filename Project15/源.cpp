#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<ctime>
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


int min_dist = INT_MAX;

void lwstBT(string a, string b, int i, int j, int edist)
{
	int n = a.length();
	int m = b.length();
	if (i == n || j == m) {
		if (i < n)  edist += (n - i);    // a长，直接加上后续多余长度
		if (j < m)  edist += (m - j);    // 同上
		if (edist < min_dist)   min_dist = edist;  // 更新最大值
		return;
	}
	if (a[i] == b[j]) {            // 两个字符匹配
		lwstBT(a, b, i + 1, j + 1, edist);
	}
	else {                       // 两个字符不匹配
		lwstBT(a, b, i + 1, j, edist + 1);   // 删除a[i]或者b[j]前添加一个字符
		lwstBT(a, b, i, j + 1, edist + 1);   // 删除b[j]或者a[i]前添加一个字符
		lwstBT(a, b, i + 1, j + 1, edist + 1); // 将a[i]和b[j]替换为相同字符
	}
}

int cmpstrab(string a, string b)
{
	min_dist = INT_MAX;
	lwstBT(a, b, 0, 0, 0);
	return min_dist;
}

int min3(int a, int b, int c) {
	a = a < b ? a : b;
	return a < c ? a : c;
}

int LevenshteinDP(string s, string t) {
	//levenshtein距离的自底向上方式的动态规划实现，把重复计算的距离存入一个矩阵中
	int dp[20][20] = {};//d[i][j]表示字符串s的前i字符和t的前j个字符的莱文斯坦距离
	for (int i = 0; i <= s.length(); i++)dp[i][0] = i;//源字符串s到空字符串t只要删除每个字符
	for (int j = 1; j <= t.length(); j++)dp[0][j] = j;//从空字符s到目标字符t只要添加每个字符
	for (int j = 0; j < t.length(); j++) {
		for (int i = 0; i < s.length(); i++) {
			if (s[i] == t[j])dp[i + 1][j + 1] = dp[i][j];//无任何操作
			else dp[i + 1][j + 1] = min3(dp[i][j + 1] + 1, dp[i + 1][j] + 1, dp[i][j] + 1);
			//分别为删除、添加、替换操作
		}
	}
	return dp[s.length()][t.length()];
}



int main()
{
	char* oneLine = new char[1000];
	fstream csvtest("a.csv");
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
	cout << "录入完成,用时" << t1 - t0 << "秒" << endl;
	csvtest.close();


	bool flag = false;
	vector<string>& v1 = person[0]._v;
	vector<string>& v2 = person[1]._v;
	if ((v1[2] == v2[2] || (v1[2].length() == v2[2].length() && LevenshteinDP(v1[2], v2[2]) < 3))
		&& v1[4] == v2[4]
		&& (v1[3] == v2[3] || (v1[3][0] == v2[3][0] && (v1[3].length() == 1 || v2[3].length() == 1 || LevenshteinDP(v1[3], v2[3]) < 4)))
		&& (v1[5] == v2[5] || (v1[5][0] == v2[5][0] && (v1[5].length() == 1 || v2[5].length() == 1 || LevenshteinDP(v1[5], v2[5]) < 4))))
	{
		flag = true;
	}
	if (flag)
		cout << "匹配成功" << endl;
	else
		cout << "匹配失败" << endl;
	return 0;
}