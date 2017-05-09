#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

//                                                          //AUTHOR:Hugo García
//                                                          //DATE: 4/23/2017
//                                                          //PURPOSE: Get the largest number you can form with
//                                                          //    n entries of m characters long.

//======================================================================================================================
int intCompareStrings(string X, string Y)
{
    string XY = X.append(Y);
    string YX = Y.append(X);

    if (XY > YX)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//----------------------------------------------------------------------------------------------------------------------
void largest_number(vector<string> arr)
{
    sort(arr.begin(), arr.end(), intCompareStrings);

    for (int intI = 0; intI < arr.size(); intI++)
    {
        std::cout << arr[intI];
    }
}

//----------------------------------------------------------------------------------------------------------------------
int main() 
{
    int intN;
    std::cin >> intN;
    vector<string> a(intN);
    for (size_t i = 0; i < a.size(); i++) 
    {
        std::cin >> a[i];
    }

    largest_number(a);
}
//======================================================================================================================