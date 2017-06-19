#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <stack>
#include <queue>
#include <map>
#include <functional>
#include <queue>
#include <bitset>
#include <sstream>
#include <set>
#include <iomanip>

using namespace std;

//															//AUTHOR: Hugo Garcia
//															//PURPOSE: Competitive programming template

//======================================================================================================================

typedef long long ll;
typedef vector<ll> vi;

//======================================================================================================================

//----------------------------------------------------------------------------------------------------------------------
int main()
{
	ll intN;

	cin >> intN;

	string str;
	int intNumber;
	map<int, string> m;
	for (ll intI = 0; intI < intN; ++intI)
	{
		cin >> str;

		if (str == "add")
		{
			cin >> intNumber >> str;

			if (m.find(intNumber) != m.end())
			{
				m.erase(intNumber);
			}

			m.insert(make_pair(intNumber, str));
		}
		else if (str == "find")
		{
			cin >> intNumber;
			if (m.find(intNumber) == m.end())
			{
				cout << "not found" << endl;
			}
			else
			{
				cout << m[intNumber] << endl;
			}
		}
		else
		{
			cin >> intNumber;
			if (m.find(intNumber) != m.end())
			{
				m.erase(intNumber);
			}
		}
	}

	return 0;
}
//======================================================================================================================