#include <iostream>

//                                                          //AUTHOR:Hugo García
//                                                          //DATE: 4/14/2017
//                                                          //PURPOSE: Get the Greatest Common Divisor of two numbers.

//======================================================================================================================
int intGCD(int intA, 
    int intB) 
{
    if (intA % intB != 0)
    {
        return intGCD(intB, intA % intB);
    }
    else
    {
        return intB;
    }
}

//----------------------------------------------------------------------------------------------------------------------
int main() 
{
    int intA, intB;
    std::cin >> intA >> intB;
    std::cout << intGCD(intA, intB) << std::endl;
    return 0;
}
//======================================================================================================================