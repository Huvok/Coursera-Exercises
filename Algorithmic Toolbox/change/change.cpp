#include <iostream>

//                                                          //AUTHOR:Hugo García
//                                                          //DATE: 4/23/2017
//                                                          //PURPOSE: Get the minimun quantity of coins of 10, 5 and 1	
using namespace std;

//======================================================================================================================
int get_change(int intMoney) 
{
    int intCoins = 0;

    while (intMoney > 0)
    {
    	if (intMoney >= 10)
    	{
    		intMoney -= 10;
    		intCoins++;
    	}
    	else if (intMoney >= 5)
    	{
    		intMoney -= 5;
    		intCoins++;
    	}
    	else if (intMoney >= 1)
    	{
    		intMoney -= 1;
    		intCoins++;
    	}
    }

    return intCoins;
}

//----------------------------------------------------------------------------------------------------------------------
int main() 
{
    int intMoney;
    std::cin >> intMoney;
    std::cout << get_change(intMoney) << '\n';
}
//======================================================================================================================