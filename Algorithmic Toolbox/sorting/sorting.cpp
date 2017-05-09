#include <iostream>
#include <vector>
#include <cstdlib>

using std::vector;
using std::swap;

//                                                          //AUTHOR: Hugo García
//                                                          //DATE: 5/1/2017
//                                                          //PURPOSE: Implement Quicksort with three partitions.

//                                                          //Only to get it to compile because I call the first
//                                                          //      function from the second one and viceversa.
void subQuick3(vector<int> &arrint, int intLow, int intHigh);

//======================================================================================================================
void subSortPartition(vector<int> &arrint, int intLow, int intHigh) 
{
    int intPivot = arrint[intLow];
    int intLowPivot = intLow;
    int intEqualElements = 0;
    int intPivotEnd = intHigh;
    for (int intI = intLow + 1; intI <= intPivotEnd; ++intI) 
    {
        if (arrint[intI] < intPivot) 
        {
        intLowPivot++;
        swap(arrint[intI], arrint[intLowPivot]);
        }
        else if (arrint[intI] == intPivot)
        {
            intEqualElements++;
        }
        else
        {
        intPivotEnd--;
        swap(arrint[intI], arrint[intPivotEnd]);
        }
    }

    swap(arrint[intLow], arrint[intLowPivot]);

    subQuick3(arrint, intLow, intLowPivot - 1);
    subQuick3(arrint, intEqualElements + intLow + 1, intHigh);
}

//----------------------------------------------------------------------------------------------------------------------
void subQuick3(vector<int> &arrint, int intLow, int intHigh) 
{
    if (intLow >= intHigh) 
    {
        return;
    }

    int intPivot = intLow + rand() % (intHigh - intLow + 1);
    swap(arrint[intLow], arrint[intPivot]);
    subSortPartition(arrint, intLow, intHigh);
}

//----------------------------------------------------------------------------------------------------------------------
int main() {
    int intN;
    std::cin >> intN;
    vector<int> arrint(intN);

    for (size_t i = 0; i < arrint.size(); ++i) 
    {
        std::cin >> arrint[i];
    }

    subQuick3(arrint, 0, arrint.size() - 1);
    for (size_t i = 0; i < arrint.size(); ++i) 
    {
        std::cout << arrint[i] << ' ';
    }
}
//======================================================================================================================