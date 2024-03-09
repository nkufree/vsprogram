#include<iostream>
#include<fstream>

using namespace std;

int main()
{
	ifstream inputsrt("a.srt");
	char str[1000] = {};
	int line = 0;
	while (inputsrt.getline(str, 1000))
	{
		if(line % 4 == 2)
			cout << str << " ";
		line++;
	}
	return 0;
}