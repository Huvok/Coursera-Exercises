#include <iostream>

//                                                          //AUTHOR:Hugo García
//                                                          //DATE: 4/14/2017
//                                                          //PURPOSE: Get the Least Common Multiplier of two numbers.

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
long long longLCM(int intA, 
	int intB) 
{
	//														//Remember that LCM(a, b) * GCM(a, b) = a * b.
	return ((long long) intA * intB) / intGCD(intA, intB);
}

//----------------------------------------------------------------------------------------------------------------------
int main() 
{
    int intA, intB;
    std::cin >> intA >> intB;
    std::cout << longLCM(intA, intB) << std::endl;
    return 0;
}
//======================================================================================================================