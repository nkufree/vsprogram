#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

class HuffmanCode
{
public:
	HuffmanCode(){}
	char s;
	int freq;
	string code;
};
HuffmanCode codeList[100] = {};

class Node
{
public:
	Node(int w):weight(w){}
	Node(int w, char s) :weight(w), m(s){}
	char m;
	int weight;
	Node* left;
	Node* right;
};

//求编码
void tcode(Node* n, string s = "")
{
	string temp1 = s;
	string temp2 = s;
	if (n->left == nullptr && n->right == nullptr)
	{
		int i;
		for (i = 0; i < 100; i++)
		{
			if (codeList[i].s == n->m)
			{
				codeList[i].code = s;
				break;
			}
		}
		cout << codeList[i].s << " " << codeList[i].code << endl;
		return;
	}
	temp1 += '0';
	temp2 += '1';
	if(n->left != nullptr)
		tcode(n->left, temp1);
	if(n->right != nullptr)
		tcode(n->right, temp2);
}

//解码
void dcode(ifstream& in, ofstream& out, Node* r)
{
	Node* root = r;
	Node* curr = r;
	string str;
	in >> str;
	int i = 0;
	while (i < str.length())
	{
		while (!(curr->left == nullptr && curr->right == nullptr))
		{
			if (str[i] == '0')
				curr = curr->left;
			else
				curr = curr->right;
			i++;
		}
		out << curr->m;
		curr = root;
	}
}

int main()
{
	int freq[2][100] = {};
	ifstream inputfile1("inputfile1.txt");
	char ch;
	int end = 52;
	int len = 0;
	while (inputfile1.get(ch))
	{
		if (ch >= 'A' && ch <= 'Z')
		{
			if (freq[0][ch - 'A'] == 0)
				freq[0][ch - 'A'] = ch;
			freq[1][ch - 'A']++;
		}
		else if(ch >= 'a' && ch <= 'z')
		{
			if (freq[0][ch - 'a' + 26] == 0)
				freq[0][ch - 'a' + 26] = ch;
			freq[1][ch - 'a' + 26]++;
		}
		else 
		{
			bool flag = false;
			for (int i = 52; freq[0][i] != 0; i++)
			{
				if (freq[0][i] == ch)
				{
					freq[1][i]++;
					flag = true;
					break;
				}	
			}
			if (!flag)
			{
				freq[0][end] = ch;
				freq[1][end]++;
				end++;
			}
		}
	}
	inputfile1.close();
	for (int i = 0; i < 100; i++)
	{
		if (freq[0][i])
		{
			codeList[i].s = char(freq[0][i]);
			codeList[i].freq = freq[1][i];
		}
	}
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 99 - i; j++)
		{
			if (freq[1][j] > freq[1][j + 1])
			{
				int temp1 = freq[0][j];
				int temp2 = freq[1][j];
				freq[0][j] = freq[0][j + 1];
				freq[1][j] = freq[1][j + 1];
				freq[0][j + 1] = temp1;
				freq[1][j + 1] = temp2;
			}
		}
	}
	int start = 0;
	for (int i = 0; freq[0][i] == 0; i++)
	{
		if (freq[0][i + 1] != 0)
			start = i + 1;
	}
	//for (int i = start; i < 100; i++)
	//	cout << setw(6) << char(freq[0][i]);
	//cout << endl;
	//for (int i = start; i < 100; i++)
	//	cout << setw(6) << freq[1][i];
	//cout << endl;
	Node* arr[100] = {};
	for (int i = start; i < 100; i++)
		arr[i-start] = new Node(freq[1][i], freq[0][i]);
	//构造Huffman树
	int i = 0;
	Node* root = nullptr;
	while (i < 99)
	{
		Node* p = new Node(arr[i]->weight + arr[i + 1]->weight);
		p->left = arr[i];
		p->right = arr[i + 1];
		arr[i] = nullptr;
		arr[i + 1] = nullptr;
		i++;
		if (arr[i + 1] == nullptr)
		{
			root = p;
			break;
		}
		if (arr[i + 1]->weight >= p->weight)
			arr[i] = p;
		else
		{
			for (int j = i + 1; j < 100; j++)
			{
				if (j == 99)
				{
					for (int k = i; k < j; k++)
						arr[k] = arr[k + 1];
					arr[j] = p;
					break;
				}
				if (arr[j] == nullptr)
				{
					arr[j] = p;
					i++;
					break;
				}
				else
				{
					if (arr[j + 1] != nullptr
						&& arr[j]->weight < p->weight
						&& arr[j + 1]->weight >= p->weight)
					{
						for (int k = i; k < j; k++)
							arr[k] = arr[k + 1];
						arr[j] = p;
						break;
					}
				}
			} 
		}
	}
	//求出各字母对应编码
	tcode(root);

	//输出编码后的文件
	ofstream outputfile("outputfile.dat",ios::out|ios::binary);
	ifstream inputfile2("inputfile2.txt");
	int len2 = 0;
	string output = "";
	char ch2;
	while (inputfile2.get(ch2))
	{
		len2++;
		for (int k = 0; k < 100; k++)
		{
			if (codeList[k].s == ch2)
			{
				output += codeList[k].code;
				break;
			}
		}
	}
	outputfile << output;
	inputfile2.close();
	outputfile.close();
	//输出各字符出现频率及编码
	ofstream outputfile1("outputfile1.txt");
	outputfile1 << left << setw(6) << "字符" 
		<< setw(10) << "出现次数" 
		<< setw(12) << "对应的编码" << endl;
	for(int j = 0; j < 100; j++)
		if (codeList[j].s)
		{
			if (codeList[j].s == ' ')
			{
				outputfile1 << setw(6) << "空格"
					<< setw(10) << codeList[j].freq
					<< setw(12) << codeList[j].code << endl;
			}
			else if (codeList[j].s == 10)
			{
				outputfile1 << setw(6) << "回车"
					<< setw(10) << codeList[j].freq
					<< setw(12) << codeList[j].code << endl;
			}
			else
			{
				outputfile1 << setw(6) << codeList[j].s
					<< setw(10) << codeList[j].freq
					<< setw(12) << codeList[j].code << endl;
			}
		}
	outputfile1.close();
	//解码
	ifstream doutputfile("outputfile.dat",ios::in|ios::binary);
	ofstream outputfile2("outputfile2.txt");
	dcode(doutputfile, outputfile2, root);
	doutputfile.close();
	outputfile2.close();

	//计算压缩比
	double abc = output.length() / (len2 * 8.0);
	cout << "压缩比为 " << output.length() << "/" << len2 * 8 << " = " << abc << endl;
	return 0;
}