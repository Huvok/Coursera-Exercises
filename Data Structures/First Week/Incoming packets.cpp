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
//                                                          //PURPOSE: Simulation of incoming packet processing.

//======================================================================================================================
int main()
{
	int intCap, intN, intA, intP;

	cin >> intCap >> intN;

	queue<pair<int, int>> q;
	queue<pair<int, int>> wait;
	int intCurrentCap = 0;
	int intCurrentTime = 0;
	int intElapsedProcessTime = 0;
	queue<int> minus;

	for (int intI = 0; intI < intN; ++intI)
	{
		cin >> intA >> intP;
		wait.push(make_pair(intA, intP));
	}

	for (int intI = 0; intI < 1000000; ++intI)
	{
		while (!wait.empty() && wait.front().first <= intI &&
			wait.front().second == 0)
		{
			cout << intI << endl;
			wait.pop();
		}

		while (!wait.empty() && wait.front().first <= intI)
		{
			if (intCurrentCap < intCap)
			{
				q.push(make_pair(wait.front().first, wait.front().second));
				intCurrentCap++;
				minus.push(1);
			}
			else
			{
				minus.push(-1);
			}

			wait.pop();
		}

		if (!q.empty()) intElapsedProcessTime++;

		if (!q.empty() && q.front().second - intElapsedProcessTime == 0)
		{
			cout << intI - intElapsedProcessTime + 1 << endl;
			q.pop();
			intElapsedProcessTime = 0;
			intCurrentCap--;
			minus.pop();
		}

		if (minus.front() == -1)
		{
			cout << -1 << endl;
			minus.pop();
		}

		if (wait.empty() && q.empty()) break;
	}

	return 0;
}
//======================================================================================================================