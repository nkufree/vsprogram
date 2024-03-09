#include <iostream>
#include <vector>

using namespace std;


int main()
{
	int n;
	cin >> n;
	vector<vector <int>> vect;
	for (int i = 0; i < n; i++)
	{
		int T;
		cin >> T;
		vector<int> vec;
		vector<int>::iterator it;

		for (int j = 0; j < T; j++)
		{
			int id;
			cin >> id;
			it = vec.begin();
			vec.insert(it, id);
			vector<int>::iterator it2;
			for (it2 = vec.begin() + 1; it2 != vec.end(); it2++)
			{
				if (*it2 == id)
				{
					vec.erase(it2);
					break;
				}
			}
		}
		vect.push_back(vec);
	}
	for (int i = 0; i < n; i++)
	{
		cout << vect[i][0];
		for (int j = 1; j < vect[i].size(); j++)
			cout << " " << vect[i][j];
		cout << endl;
	}
	return 0;
}