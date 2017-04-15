#include <iostream>

//                                                          //AUTHOR:Hugo García
//                                                          //DATE: 4/14/2017
//                                                          //PURPOSE: Get the last digit of the sum from F0 to Fn.

//======================================================================================================================
long long longFibonacciSum(long long longN) 
{
    //                                                      //Pisano period of 10 is 60 (We need %10 for the last digit)
    longN = (longN + 2) % 60;
    int arrint[longN + 1];
    arrint[0] = 0;
    arrint[1] = 1;

    for (int intI = 2; intI <= longN; intI++) 
    {
        //                                                  //Get last digit of both past last digits, then get the
        //                                                  //      last digit of their sum.
        arrint[intI] = (arrint[intI - 1] % 10 + arrint[intI - 2] % 10) % 10;
    }

    //                                                      //We will get the last digit + 1, so if the last digit is
    //                                                      //      9, we will have a 10, i.e. 0.
    if(arrint[longN] == 0)
    {
        return 9;
    }

    return (arrint[longN] % 10 - 1);
}

//----------------------------------------------------------------------------------------------------------------------
int main() 
{
    long long longN;
    std::cin >> longN;
    std::cout << longFibonacciSum(longN) << '\n';
}
//======================================================================================================================