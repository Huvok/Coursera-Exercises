#include <iostream>


//                                                          //AUTHOR:Hugo García
//                                                          //DATE: 4/14/2017
//                                                          //PURPOSE: Implement a fast algorithm for the fibonacci 
//                                                          //      sequence.

//======================================================================================================================
int intFibonacci(int intN) 
{
    int arrint[intN];
    arrint[0] = 0;
    arrint[1] = 1;

    for (int intI = 2; intI < intN + 1; intI++)
    {
        arrint[intI] = arrint[intI - 1] + arrint[intI - 2];
    }

    return arrint[intN];
}

//----------------------------------------------------------------------------------------------------------------------
int main() 
{
    int intN;
    std::cin >> intN;
    std::cout << intFibonacci(intN) << '\n';
    return 0;
}
//======================================================================================================================