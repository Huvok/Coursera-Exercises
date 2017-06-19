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
ll mulmod(ll a, ll b, ll m) {
	ll ret = 0;
	while (b) {
		if (b & 1) ret = (ret + a) % m; // Problema interesante: supongamos que ret+a puede excederse de 2^64 bits, como hacerle para no tener overflow??
		a = (a << 1) % m;
		b >>= 1;
	}
	return ret;
}

// x^n mod m (tambien se usa la notacion x**n mod m)
// O(logN)
ll fastPow(ll x, ll n, ll m) {
	ll ret = 1;
	while (n) {
		if (n & 1) ret = mulmod(ret, x, m); // Recordar que solo lo tenemos que usar si MOD>2^32, sino usar ret=ret*x%m;, ya que es tiempo constante
		x = mulmod(x, x, m);
		n >>= 1;
	}
	return ret;
}

//----------------------------------------------------------------------------------------------------------------------
int main()
{
	ll intN, intM;

	cin >> intM;
	cin >> intN;

	string str;
	ll intNumber;
	map<ll, vector<string>> m;
	for (ll intI = 0; intI < intN; ++intI)
	{
		cin >> str;

		if (str == "add")
		{
			intNumber = 0;
			cin >> str;

			for (ll intJ = 0; intJ < str.length(); ++intJ)
			{
				intNumber += ((ll)str[intJ] * fastPow(263, intJ, 1000000007));
			}

			intNumber %= 1000000007;
			intNumber %= intM;
			vector<string> v;
			if (m.find(intNumber) != m.end())
			{
				v = m[intNumber];
				m.erase(intNumber);
			}

			v.push_back(str);
			m.insert(make_pair(intNumber, v));
		}
		else if (str == "check")
		{
			cin >> intNumber;
			if (m.find(intNumber) == m.end())
			{
				cout << endl;
			}
			else
			{
				for (ll intK = m[intNumber].size() - 1; intK >= 0; --intK)
				{
					cout << m[intNumber][intK] << " ";
				}

				cout << endl;
			}
		}
		else if (str == "find")
		{
			intNumber = 0;
			cin >> str;

			for (ll intJ = 0; intJ < str.length(); ++intJ)
			{
				intNumber += ((int)str[intJ] * fastPow(263, intJ, 1000000007));
			}

			intNumber %= 1000000007;
			intNumber %= intM;

			if (m.find(intNumber) == m.end())
			{
				cout << "no" << endl;
			}
			else
			{
				for (ll intK = 0; intK < m[intNumber].size(); ++intK)
				{
					if (m[intNumber][intK] == str)
					{
						cout << "yes" << endl;
						break;
					}

					if (intK == m[intNumber].size() - 1)
					{
						cout << "no" << endl;
					}
				}
			}
		}
		else
		{
			intNumber = 0;
			cin >> str;

			for (ll intJ = 0; intJ < str.length(); ++intJ)
			{
				intNumber += ((int)str[intJ] * fastPow(263, intJ, 1000000007));
			}

			intNumber %= 1000000007;
			intNumber %= intM;

			vector<string> v;
			if (m.find(intNumber) != m.end())
			{
				for (ll intK = 0; intK < m[intNumber].size(); intK++)
				{
					if (m[intNumber][intK] != str)
					{
						v.push_back(m[intNumber][intK]);
					}
				}

				m.erase(intNumber);

				if (v.size() > 0)
					m.insert(make_pair(intNumber, v));
			}
		}
	}

	return 0;
}
//======================================================================================================================