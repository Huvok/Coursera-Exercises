#include <iostream>
#include <vector>

using std::vector;
using namespace std;

//                                                          //AUTHOR: Hugo García
//                                                          //DATE: 5/1/2017
//                                                          //PURPOSE: Count the number of inversions in a merge sort.

//======================================================================================================================
long long longMerge(vector<int> &arrint, 
    vector<int> &arrintAux, 
    size_t intLeftFirst, 
    size_t intRightFirst, 
    size_t intLeftSecond, 
    size_t intRightSecond) 
{
    int intCount = 0;
    int intIndex = 0;
    while (intLeftFirst <= intRightFirst &&
        intLeftSecond <= intRightSecond)
    {
        if (arrint[intLeftFirst] <= arrint[intLeftSecond])
        {
            arrintAux[intIndex] = arrint[intLeftFirst];
            intLeftFirst++;
        }
        else
        {
            arrintAux[intIndex] = arrint[intLeftSecond];
            intLeftSecond++;
            intCount++;
        }

        intIndex++;
    }

    for (int intI = intLeftFirst; intI < intRightFirst; ++intI)
    {
        arrintAux[intIndex] = arrint[intI];
        intIndex++;
    }

    for (int intI = intRightFirst; intI < intRightSecond; ++intI)
    {
        arrintAux[intIndex] = arrint[intI];
        intIndex++;
    }

    return intCount;
}

//----------------------------------------------------------------------------------------------------------------------
long long longMergeSort(vector<int> &arrint, 
    vector<int> &arrintAux, 
    int intLeft, 
    int intRight) 
{
    long long intCount = 0;
    if (intLeft >= intRight)
    {
        return intCount;
    }

    int intMiddle = intLeft + (intRight - intLeft) / 2;
    intCount += longMergeSort(arrint, arrintAux, intLeft, intMiddle);
    intCount += longMergeSort(arrint, arrintAux, intMiddle + 1, intRight);


    intCount += longMerge(arrint, arrintAux, intLeft, intMiddle, intMiddle + 1, intRight);
    return intCount;
}

//----------------------------------------------------------------------------------------------------------------------
int main() {
    int intN;
    std::cin >> intN;
    vector<int> arrint(intN);
    for (int i = 0; i < arrint.size(); i++) 
    {
        std::cin >> arrint[i];
    }
    vector<int> arrintAux(arrint.size());
    std::cout << longMergeSort(arrint, arrintAux, 0, arrint.size()) << '\n';
}
//======================================================================================================================