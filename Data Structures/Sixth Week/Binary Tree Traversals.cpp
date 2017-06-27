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
void subInorder(ll root)
{
	if (arr[root].second.first != -1)
	{
		subInorder(arr[root].second.first);
	}

	printf("%lld ", arr[root].first);

	if (arr[root].second.second != -1)
	{
		subInorder(arr[root].second.second);
	}
}

void subPreorder(ll root)
{
	printf("%lld ", arr[root].first);

	if (arr[root].second.first != -1)
	{
		subPreorder(arr[root].second.first);
	}

	if (arr[root].second.second != -1)
	{
		subPreorder(arr[root].second.second);
	}
}

void subPostorder(ll root)
{
	if (arr[root].second.first != -1)
	{
		subPostorder(arr[root].second.first);
	}

	if (arr[root].second.second != -1)
	{
		subPostorder(arr[root].second.second);
	}

	printf("%lld ", arr[root].first);
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

	subInorder(0);
	printf("\n");
	subPreorder(0);
	printf("\n");
	subPostorder(0);
	printf("\n");

	return 0;
}
//======================================================================================================================