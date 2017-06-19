#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <stack>
#include <queue>

using namespace std;
typedef unsigned long long ll;

//                                                          //AUTHOR: Hugo García
//                                                          //DATE: 5/28/2017
//                                                          //PURPOSE: Get the height of a BT.

//======================================================================================================================
struct Node
{
	vector<int> lst;
};

//======================================================================================================================
Node arr[500000];
int main()
{
	int intN;
	cin >> intN;

	Node root;
	int intRoot;

	for (int intI = 0; intI < intN; ++intI)
	{
		int intNext;
		cin >> intNext;
		if (intNext == -1)
		{
			root = arr[intI];
			intRoot = intI;
		}
		else
		{
			arr[intNext].lst.push_back(intI);
		}
	}

	queue<int> q;
	q.push(intRoot);
	int intAux;
	int intLevel = 0;
	int intChamp = 0;
	int intCurrentOffset = 1;
	int intNextOffset = 0;
	bool needToUpdate = false;
	while (!q.empty())
	{
		intCurrentOffset--;

		intAux = q.front();
		q.pop();

		for (int intI = 0; intI < arr[intAux].lst.size(); ++intI)
		{
			q.push(arr[intAux].lst[intI]);
			intNextOffset++;
		}

		if (intCurrentOffset == 0)
		{
			intLevel++;
			intCurrentOffset = intNextOffset;
			intNextOffset = 0;
		}

		intChamp = max(intChamp, intLevel);
	}

	cout << intChamp << endl;

	return 0;
}
//======================================================================================================================