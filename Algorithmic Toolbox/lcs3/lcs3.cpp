#include <iostream>
#include <vector>
#include <algorithm>

//                                                          //AUTHOR:Hugo García
//                                                          //DATE: 5/21/2017
//                                                          //PURPOSE: Get the maximum subsequence between 3 strings.
using namespace std;

//======================================================================================================================
int arr[101][101][101];

long long lcs3(vector<long long> &a, vector<long long> &b, vector<long long> &c)
{
	for (int intI = 0; intI <= a.size(); intI++)
	{
		for (int intJ = 0; intJ <= b.size(); intJ++)
		{
			for (int intK = 0; intK <= c.size(); intK++)
			{
				if (intI == 0 || intJ == 0 || intK == 0)
				{
					arr[intI][intJ][intK] = 0;
				}
				else if (a[intI - 1] == b[intJ - 1] &&
					a[intI - 1] == c[intK - 1])
				{
					arr[intI][intJ][intK] = arr[intI - 1][intJ - 1][intK - 1] + 1;
				}
				else
				{
					arr[intI][intJ][intK] = max(arr[intI - 1][intJ][intK],
						max(arr[intI][intJ][intK - 1], arr[intI][intJ - 1][intK]));
				}
			}
		}
	}

	return arr[a.size()][b.size()][c.size()];
}

//----------------------------------------------------------------------------------------------------------------------
int main() 
{
	long long an;
	std::cin >> an;
	vector<long long> a(an);
	for (size_t i = 0; i < an; i++) 
	{
		std::cin >> a[i];
	}
	long long bn;
	std::cin >> bn;
	vector<long long> b(bn);
	for (size_t i = 0; i < bn; i++) 
	{
		std::cin >> b[i];
	}
	long long cn;
	std::cin >> cn;
	vector<long long> c(cn);
	for (size_t i = 0; i < cn; i++) 
	{
		std::cin >> c[i];
	}
	std::cout << lcs3(a, b, c) << std::endl;
}
//======================================================================================================================