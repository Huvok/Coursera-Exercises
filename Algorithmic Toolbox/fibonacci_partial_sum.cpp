#include <iostream>
//                                                          //AUTHOR:Hugo García
//                                                          //DATE: 4/14/2017
//                                                          //PURPOSE: Get the last digit of the sum from F0 to Fn.

//======================================================================================================================
long long longGetFiboModulus(long long longNewFibonacci, long long longOldFibonacci)
{
	long long longA = 1, longB = 1, longC = 1, longD = 0, longAuxA, longAuxB, longResult = 0 % longOldFibonacci, 
		longAuxC, longAuxD = 1 % longOldFibonacci;

	while (longNewFibonacci)
	{
		if (longNewFibonacci & 1)
		{
			longAuxC = longResult;
			longResult = (longResult*longA + longAuxD*longC) % longOldFibonacci;
			longAuxD = (longAuxC*longB + longAuxD*longD) % longOldFibonacci;
		}

		longAuxA = longA; longAuxB = longB; longAuxC = longC;
		longA = (longA*longA + longB*longC) % longOldFibonacci;
		longB = (longAuxA*longB + longB*longD) % longOldFibonacci;
		longC = (longC*longAuxA + longD*longC) % longOldFibonacci;
		longD = (longAuxC*longAuxB + longD*longD) % longOldFibonacci;

		longNewFibonacci >>= 1;
	}

	return longResult;
}

//----------------------------------------------------------------------------------------------------------------------
long long intGetFibonacci(long long longN, long long longM) 
{
	//														//Uses the principle of the Pisano Period.
	long long longMinus2 = 0 % longM, longMinus1 = 1 % longM, longAux;
	long long longPisanoPeriod, longNewFibonacci;
	for (long long longI = 1; longI <= longM*longM - 1; longI++) 
	{
		longAux = longMinus2;
		longMinus2 = longMinus1;
		longMinus1 = (longAux + longMinus2) % longM;
		longPisanoPeriod = longI;

		//													//Found Pisano Period.
		if (longMinus2 == 0 && longMinus1 == 1)
		{
			break;
		}
	}

	longNewFibonacci = longN;

	while (longNewFibonacci >= longPisanoPeriod) 
	{
		longNewFibonacci = longNewFibonacci % longPisanoPeriod;
	}

	return longGetFiboModulus(longNewFibonacci, longM);
}

//----------------------------------------------------------------------------------------------------------------------
long long longFibonacciPartialSum(long long longN, 
	long long longM) 
{
	//														//We need to get the exact fibonacci % 10.
	if (longN == longM) 
	{
		return intGetFibonacci(longN, 10);
	}

	//														//To get the sum of all F0 to FM, we use F(M + 2).
	long long longMPlus2 = longM + 2, longNPlus1 = longN + 1;
	//														//Minus one because if a sum gets 10, this will return 0.
	int intFiboN = (intGetFibonacci(longMPlus2, 10) - 1) % 10;
	int intFiboM = (intGetFibonacci(longNPlus1, 10) - 1) % 10;

	if (intFiboM > intFiboN) 
	{
		return intFiboN + 10 - intFiboM;
	}
	else 
	{
		return intFiboN - intFiboM;
	}
}

//----------------------------------------------------------------------------------------------------------------------
int main() 
{
	long long longN, longM;
	std::cin >> longN >> longM;
	std::cout << longFibonacciPartialSum(longN, longM) << '\n';
}
//======================================================================================================================