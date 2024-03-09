#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main()
{
	ifstream poems("Poems.txt");
	char* str = new char[200];
	string in = "";
	string out = "";
	string strT = "T: ";
	string strP = "P: ";
	int l = 0;
	int w = 0;
	while (!poems.eof())
	{
		poems >> in;
		if (str[0] == '\0')
			continue;
		else if (in == "Title:")
		{
			poems.getline(str, 200);
			strT += str;
		}
		else if (in == "Poet:")
		{
			poems.getline(str, 200);
			strP += str;
		}
		else
		{
			int count = 1;
			for (int i = 0; i < in.length(); i++)
			{
				if (in[i] == '\'')
					count++;
			}

			w += count;

		}
		int i = 0;
		while (str[i] != ' ')
		{
			str2 += str[i++];
		}
		if (str2 == "title:")
		{

		}
		cout << str2 << endl;
	}

}