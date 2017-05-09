#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;

//                                                          //AUTHOR: Hugo García
//                                                          //DATE: 5/1/2017
//                                                          //PURPOSE: Get the majority element of a set.

//======================================================================================================================
int get_majority_element(vector<int> &arrint) 
{
    int intCurrentMajIndex = 0;
    int intCount = 1;
    for (int intI = 1; intI < arrint.size(); ++intI)
    {
        if (arrint[intI] == arrint[intCurrentMajIndex])
        {
            intCount++;
        }
        else if (arrint[intI] != arrint[intCurrentMajIndex])
        {
            intCount--;
        }

        if (intCount == 0)
        {
            intCurrentMajIndex = intI;
            intCount = 1;
        }
    }

    intCount = 0;

    for (int intI = 0; intI < arrint.size(); ++intI)
    {
        if (arrint[intCurrentMajIndex] == arrint[intI])
        {
            intCount++;
        }
    }

    if (intCount > arrint.size() / 2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//----------------------------------------------------------------------------------------------------------------------
int main() 
{
    int n;
    std::cin >> n;
    vector<int> a(n);
    for (size_t i = 0; i < a.size(); ++i) 
    {
        std::cin >> a[i];
    }
    std::cout << (get_majority_element(a)) << '\n';
}
//======================================================================================================================