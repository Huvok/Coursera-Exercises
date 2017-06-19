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
#define rep(i,j,k) for (ll (i)=(j);(i)<=(k);++(i))

using namespace std;

typedef long long ll;
typedef vector<ll> vi;

class UnionFind
{
private:
	vi p, rank, aux;
	ll champ;

public:
	UnionFind(ll N, vi v)
	{
		champ = 0;
		rank.assign(N, 0);
		aux.assign(N, 0);
		for (ll intI = 0; intI < N; ++intI)
		{
			aux[intI] = v[intI];
			champ = max(champ, aux[intI]);
		}
		p.assign(N, 0);
		for (ll i = 0; i < N; i++)
		{
			p[i] = i;
		}
	}

	ll findSet(ll i)
	{
		return (p[i] == i) ? i : (p[i] = findSet(p[i]));
	}

	bool isSameSet(ll i, ll j)
	{
		return findSet(i) == findSet(j);
	}

	void unionSet(ll i, ll j)
	{
		if (!isSameSet(i, j))
		{
			ll x = findSet(i), y = findSet(j);
			
				p[y] = x;
				aux[x] += aux[y];
				champ = max(champ, aux[x]);
		}
	}

	ll getMax()
	{
		return champ;
	}
};
//----------------------------------------------------------------------------------------------------------------------
int main()
{
	ll intN, intM;
	cin >> intN >> intM;
	vi v(intN);

	for (ll intI = 0; intI < intN; ++intI)
	{
		cin >> v[intI];
	}

	UnionFind uf(intN, v);

	ll a, b;
	for (ll intI = 0; intI < intM; ++intI)
	{
		cin >> a >> b;
		uf.unionSet(a - 1, b - 1);
		cout << uf.getMax() << endl;
	}

	return 0;
}
//======================================================================================================================