#include<iostream>
#include<fstream>

using namespace std;

int main()
{
	ifstream input("input.txt");
	ofstream output("output.txt");
	char s[1000] = {};
	input.getline(s, 1000);
	while (input.getline(s, 1000))
	{
		string str = s;
		int k = str.find(" ");
		str = str.substr(k + 1);
		cout << str << endl;
		output << str << endl;
	}
	input.close();
	output.close();
	return 0;
}