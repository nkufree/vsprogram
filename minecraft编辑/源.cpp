#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	long count = 0;
	char tri[547825] = {};
	ifstream map("tri.schematic", ios::binary);
	char c;
	while ((c = map.get()) != EOF) {  // ¶ÁÖÁÎÄ¼şÎ²
		tri[count] = c;
		count++;
	}
	cout << count << endl;

	ofstream text("text.schematic", ios::binary);
	for(int i = 0; i < count; i++)
	{
		if (tri[i] == 'e' && tri[i + 1] == 'x' && tri[i + 2] == 'e' && tri[i + 3] == 'c' && tri[i + 4] == 'u' && tri[i + 5] == 't' && tri[i + 6] == 'e')
		{
			string r = "execute @a ~ ~ ~";
			string s = "execute at @a run";
			for(int i = 0; i < s.length(); i++)
				text.write(&s[i], sizeof(s[i]));
			i += r.length() - 1;
		}
		else
		{
			text.write(&tri[i], sizeof(tri[i]));
		}
	}
	/*string str = "execute @a ~ ~ ~";
	for (int i = 0; i < str.length(); i++)
	{
		cout << hex << int(str[i]) << " ";
	}
	return 0;*/

	/*ofstream text("text.schematic", ios::binary);
	ifstream a("a.txt");
	string s;
	while (a >> s)
	{
		const char* ss = s.data();
		char ch = atoi(ss);
		text.write(&ch,sizeof(ch));
	}*/
}