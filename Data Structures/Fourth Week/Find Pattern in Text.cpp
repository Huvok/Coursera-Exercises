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
	string strPattern, strText;
	ll intPrime = 101;

	cin >> strPattern >> strText;

	ll M = strPattern.length();
	ll N = strText.length();
	ll i, j;
	ll intHashPattern = 0;
	ll intHashText = 0;
	ll h = 1;

	for (i = 0; i < M - 1; i++)
	{
		h = (h * 256) % intPrime;
	}

	for (i = 0; i < M; i++)
	{
		intHashPattern = (256* intHashPattern + strPattern[i]) % intPrime;
		intHashText = (256* intHashText + strText[i]) % intPrime;
	}

	for (i = 0; i <= N - M; i++)
	{
		if (intHashPattern == intHashText)
		{
			for (j = 0; j < M; j++)
			{
				if (strText[i + j] != strPattern[j])
					break;
			}

			if (j == M)
			{
				printf("%d ", i);
			}
		}

		if (i < N - M)
		{
			intHashText = (256*(intHashText - strText[i] * h) + strText[i + M]) % intPrime;

			if (intHashText < 0)
			{
				intHashText = (intHashText + intPrime);
			}
		}
	}
	

	return 0;
}
//======================================================================================================================