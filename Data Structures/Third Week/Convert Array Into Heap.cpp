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

ll intSwaps = 0;
vector<pair<int, int>> vp;

void siftDown(ll intI, ll intN, vector<ll> &v)
{
	ll intMaxIndex = intI;
	ll l = intI * 2;
	if (l <= intN &&
		v[l] < v[intMaxIndex])
	{
		intMaxIndex = l;
	}

	ll r = intI * 2 + 1;
	if (r <= intN && v[r] < v[intMaxIndex])
	{
		intMaxIndex = r;
	}

	if (intI != intMaxIndex)
	{
		swap(v[intI], v[intMaxIndex]);
		intSwaps++;
		vp.push_back(make_pair(intI - 1, intMaxIndex - 1));
		siftDown(intMaxIndex, intN, v);
	}
}

//----------------------------------------------------------------------------------------------------------------------
int main()
{
	ll intN;
	cin >> intN;
	vector<ll> v(intN + 1);

	for (ll intI = 1; intI <= intN; ++intI)
	{
		cin >> v[intI];
	}

	ll intAux;
	for (ll intI = intN / 2; intI >= 1; --intI)
	{
		siftDown(intI, intN, v);
	}

	cout << intSwaps << endl;
	for (ll intI = 0; intI < vp.size(); ++intI)
	{
		cout << vp[intI].first << " " << vp[intI].second << endl;
	}

	return 0;
}
//======================================================================================================================