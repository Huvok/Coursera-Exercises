#include <iostream>

//                                                          //AUTHOR:Hugo García
//                                                          //DATE: 4/14/2017
//                                                          //PURPOSE: Get the modulus of a fibonacci number.

//======================================================================================================================
long long longPisanoPeriod(long long longM) 
{
    long long longMinus2 = 0, longMinus1 = 1, longCurrent = 1;
    for (int intI = 0; intI < longM * longM; intI++)
     {
        longCurrent = (longMinus2 + longMinus1) % longM;
        longMinus2 = longMinus1;
        longMinus1 = longCurrent;
        if (longMinus2 == 0 && longMinus1 == 1) 
            return intI + 1;
    }
}

//----------------------------------------------------------------------------------------------------------------------
long long longFibonacciHuge(long long longN, 
    long long longM) 
{
    long long longNewFibo = longN % longPisanoPeriod(longM);

    long long longMinus2 = 0;
    long long longMinus1 = 1;

    long long longCurrent = 1;

    for (int intI = 2; intI <= longNewFibo; intI++) 
    {
        longCurrent = (longMinus2 + longMinus1) % longM;
        longMinus2 = longMinus1;
        longMinus1 = longCurrent;
    }

    return longCurrent % longM;
}

//----------------------------------------------------------------------------------------------------------------------
int main() 
{
    long long longN, longM;
    std::cin >> longN >> longM;
    std::cout << longFibonacciHuge(longN, longM) << '\n';
}
//======================================================================================================================