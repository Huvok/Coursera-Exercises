#include <iostream>
#include <cassert>
#include <vector>

using std::vector;

//                                                          //AUTHOR: Hugo García
//                                                          //DATE: 5/1/2017
//                                                          //PURPOSE: Implement the binary search algorithm.

//======================================================================================================================
int intBinarySearch(const vector<int> &arrint, int intNumber) 
{
    int intLeft = 0, intRight = (int)arrint.size() - 1, intMiddle; 
    
    while (intLeft <= intRight)
    {
        intMiddle = intLeft + ((intRight - intLeft) / 2);
        if (arrint[intMiddle] == intNumber)
        {
            return intMiddle;
        }
        else if (intNumber < arrint[intMiddle])
        {
            intRight = intMiddle - 1;
        }
        else
        {
            intLeft = intMiddle + 1;
        }
    }

    return -1;
}

//----------------------------------------------------------------------------------------------------------------------
int main() 
{
    int intN;
    std::cin >> intN;
    vector<int> arrint(intN);

    for (size_t intI = 0; intI < arrint.size(); intI++)
    {
        std::cin >> arrint[intI];
    }

    int intTestNumbers;
    std::cin >> intTestNumbers;
    vector<int> arrintTest(intTestNumbers);

    for (int i = 0; i < intTestNumbers; ++i) 
    {
        std::cin >> arrintTest[i];
    }

    for (int i = 0; i < intTestNumbers; ++i) 
    {
        std::cout << intBinarySearch(arrint, arrintTest[i]) << ' ';
    }
}
//======================================================================================================================