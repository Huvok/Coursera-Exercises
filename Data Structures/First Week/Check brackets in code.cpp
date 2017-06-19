#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <stack>

using namespace std;
typedef unsigned long long ll;

//                                                          //AUTHOR: Hugo García
//                                                          //DATE: 5/28/2017
//                                                          //PURPOSE: Check if the brackets are correctly balanced.

//======================================================================================================================
int main()
{
	string str;

	cin >> str;

	stack<char> stack;
	std::stack<int> intstack;

	for (int intI = 0; intI < str.length(); ++intI)
	{
		if (str[intI] == '{' ||
			str[intI] == '}' ||
			str[intI] == '(' ||
			str[intI] == ')' ||
			str[intI] == '[' ||
			str[intI] == ']')
		{
			if (str[intI] == '{' ||
				str[intI] == '(' ||
				str[intI] == '[')
			{
				stack.push(str[intI]);
				intstack.push(intI);
			}
			else
			{
				if (stack.empty())
				{
					cout << intI + 1 << endl;
					return 0;
				}
				if (str[intI] == ']' && stack.top() == '[')
				{
					stack.pop();
				}
				else if (str[intI] == ')' && stack.top() == '(')
				{
					stack.pop();
				}
				else if (str[intI] == '}' && stack.top() == '{')
				{
					stack.pop();
				}
				else
				{
					cout << intI + 1 << endl;
					return 0;
				}

				intstack.pop();
			}
		}
	}

	if (!stack.empty())
	{
		int intMiss;

		while (!intstack.empty())
		{
			intMiss = intstack.top();
			intstack.pop();
		}

		cout << intMiss + 1 << endl;
		return 0;
	}

	cout << "Success" << endl;

	return 0;
}
//======================================================================================================================