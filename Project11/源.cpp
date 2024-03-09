#include<iostream>]
#include<fstream>
using namespace std;

int main()
{
	ifstream inputfile("inputfile.txt");
	ofstream outputfile("outputfile.txt");
	char ch;
	while (inputfile.get(ch))
	{
		outputfile << ch;
	}
	return 0;
}