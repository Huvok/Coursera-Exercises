#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

//                                                          //AUTHOR: Hugo García
//                                                          //DATE: 5/18/2017
//                                                          //PURPOSE: Maximize an algebraic equation by placing
//                                                          //    parentheses.

//======================================================================================================================
long long intGetResult(long long a, long long b, char op)
{
    if (op == '+')
    {
        return a + b;
    }
    else if (op == '-')
    {
        return a - b;
    }
    else if (op == '*')
    {
        return a * b;
    }
    else
    {
        return a / b;
    }
}

//----------------------------------------------------------------------------------------------------------------------
long long get_maximum_value(const string &exp) 
{
    vector<vector<long long>> arrMax(exp.length() / 2 + 1, vector<long long>(exp.length() / 2 + 1));
	vector<vector<long long>> arrMin(exp.length() / 2 + 1, vector<long long>(exp.length() / 2 + 1));

	vector<long long> arr(exp.length() / 2 + 1);
	vector<char> arrstr(exp.length() / 2);

    int intAux = 0;
    for (int intI = 0; intI < exp.length(); intI = intI + 2)
    {
        arr[intAux] = exp[intI] - '0';
        intAux++;
    }

    intAux = 0;
    for (int intI = 1; intI < exp.length(); intI = intI + 2)
    {
        arrstr[intAux] = exp[intI];
        intAux++;
    }

    for (int intI = 0; intI < exp.length() / 2 + 1; intI++)
    {
        arrMax[intI][intI] = arr[intI];
        arrMin[intI][intI] = arr[intI];
    }

    for (int intI = 0; intI < exp.length() / 2; intI++)
    {
        arrMax[intI][intI + 1] = intGetResult(arrMax[intI][intI], arrMax[intI + 1][intI + 1], arrstr[intI]);
        arrMin[intI][intI + 1] = intGetResult(arrMin[intI][intI], arrMin[intI + 1][intI + 1], arrstr[intI]);
    }

	long long max;
	long long min;
	int intOffset = 0;
	for (int intJ = 2; intJ < exp.length() / 2 + 1; intJ++)
	{
		for (int intI = 0; intI < exp.length() / 2 + 1 - intJ; intI++)
		{
			for (int intK = intI; intK < intJ + intI; intK++)
			{
				if (intK - intI == 0)
				{
					if (arrstr[intK] == '+')
					{
						max = arrMax[intI][intK] + arrMax[1 + intK][intJ + intI];
						min = arrMin[intI][intK] + arrMin[1 + intK][intJ + intI];
					}
					else if (arrstr[intK] == '*')
					{
						max = arrMax[intI][intK] * arrMax[1 + intK][intJ + intI];
						min = arrMin[intI][intK] * arrMin[1 + intK][intJ + intI];
					}
					else
					{
						max = arrMax[intI][intK] - arrMin[1 + intK][intJ + intI];
						min = arrMin[intI][intK] - arrMax[1 + intK][intJ + intI];
					}
				}
				else if (arrstr[intK] == '+')
				{
					max = std::max(max, arrMax[intI][intK] + arrMax[1 + intK][intJ + intI]);
					min = std::min(min, arrMin[intI][intK] + arrMin[1 + intK][intJ + intI]);
				}
				else if (arrstr[intK] == '*')
				{
					max = std::max(max, arrMax[intI][intK] * arrMax[1 + intK][intJ + intI]);
					min = std::min(min, arrMin[intI][intK] * arrMin[1 + intK][intJ + intI]);
				}
				else
				{
					min = std::min(min, arrMin[intI][intK] - arrMax[1 + intK][intJ + intI]);
					max = std::max(max, arrMax[intI][intK] - arrMin[1 + intK][intJ + intI]);
				}
			}

			arrMax[intI][intJ + intI] = max;
			arrMin[intI][intJ + intI] = min;
		}

		intOffset++;
	}

    return arrMax[0][exp.length() / 2];
}

//----------------------------------------------------------------------------------------------------------------------
int main() 
{
    string s;
    std::cin >> s;
    std::cout << get_maximum_value(s) << '\n';
}
//======================================================================================================================