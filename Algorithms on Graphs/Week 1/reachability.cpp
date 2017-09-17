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
#include <string.h>
#include <unordered_map>

using namespace std;

//															//AUTHOR: Hugo Garcia
//															//PURPOSE: Competitive programming template

//======================================================================================================================

#define FOR(i, a, b) for(ll i=ll(a); i<ll(b); i++)
#define pb push_back
#define mp make_pair

typedef long long ll;
typedef vector<ll> vi;
typedef pair<ll, ll> ii;
typedef vector<ii> vii;

//----------------------------------------------------------------------------------------------------------------------
vi AdjList[1005];
bool vis[1005];

void dfs(ll intS)
{
	vis[intS] = true;

	FOR(intI, 0, AdjList[intS].size())
	{
		if (!vis[AdjList[intS][intI]]) dfs(AdjList[intS][intI]);
	}
}

//----------------------------------------------------------------------------------------------------------------------
int main()
{
	ll intN, intM;
	ll intS, intD;

	cin >> intN >> intM;

	FOR(intI, 0, intM)
	{
		cin >> intS >> intD;
		AdjList[intS].pb(intD);
		AdjList[intD].pb(intS);
	}

	cin >> intS >> intD;

	dfs(intS);

	if (vis[intD]) cout << 1 << endl;
	else cout << 0 << endl;

	return 0;
}
//======================================================================================================================