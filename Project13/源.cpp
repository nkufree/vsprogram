#include<iostream>
#include<regex>

using namespace std;

int main()
{
	smatch sm;
	regex re("[^aeiou]*[aeiou][^aeiou](?=[^aeiou][aeiou])|[^aeiou]+[aeiou](?=[aeiou]|[^aeiou][aeiou])|[aeiou]+[^aeiou]+|[^aeiou][aeiou][^aeiou]+|[a-z]+|\'",regex::icase);
	regex pattern("\\d{4}");
    string str;
    string temp;
    while (cin >> str)
    {
        string::const_iterator iterStart = str.begin();
        string::const_iterator iterEnd = str.end();
        while (regex_search(iterStart, iterEnd, sm, re))
        {
            temp = sm[0];
            cout << temp << " ";
            iterStart = sm[0].second;	//更新搜索起始位置,搜索剩下的字符串
        }
        cout << endl;
    }
    
    cout << endl;
	return 0;
}