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

using namespace std;

//															//AUTHOR: Hugo Garcia
//															//PURPOSE: Competitive programming template

//======================================================================================================================

typedef long long ll;
typedef vector<ll> vi;

//======================================================================================================================
pair<int, pair<int, int>> arr[100005];

bool boolCheckBST(ll root, ll intMin, ll intMax)
{
	if (root == -1) return true;

	if (arr[root].first < intMin ||
		arr[root].first > intMax)
	{
		return false;
	}

	return (boolCheckBST(arr[root].second.first, intMin, arr[root].first - 1) &&
		boolCheckBST(arr[root].second.second, arr[root].first + 1, intMax));
}

//----------------------------------------------------------------------------------------------------------------------
int main()
{
	ll intN, intKey, intL, intR;

	scanf("%lld", &intN);
	memset(arr, 0, sizeof arr);

	for (ll intI = 0; intI < intN; intI++)
	{
		scanf("%lld %lld %lld", &intKey, &intL, &intR);
		arr[intI] = make_pair(intKey, make_pair(intL, intR));
	}

	if (!intN)
	{
		printf("CORRECT\n");
	}
	else if (boolCheckBST(0, -5000000000000000, 5000000000000000))
	{
		printf("CORRECT\n");
	}
	else
	{
		printf("INCORRECT\n");
	}

	return 0;
}
//======================================================================================================================