#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//                                                          //AUTHOR: Hugo García
//                                                          //DATE: 5/18/2017
//                                                          //PURPOSE: Calculate the minimum number of N*3, N*2 and N+1
//                                                          //      operations to reach a number.

//======================================================================================================================
vector<int> optimal_sequence(int n) 
{
    std::vector<int> sequence;
    int arr[n + 1];
    arr[1] = 1;
    for (int intI = 2; intI < n + 1; intI++)
    {
        if (intI % 3 == 0)
        {
            if (intI % 2 == 0)
            {
                arr[intI] = min(min(arr[intI / 3], arr[intI / 2]), arr[intI - 1]) + 1;
            }
            else
            {
                arr[intI] = min(arr[intI / 3], arr[intI - 1]) + 1;
            }
        }
        else if (intI % 2 == 0)
        {
            arr[intI] = min(arr[intI / 2], arr[intI - 1]) + 1;
        }
        else
        {
            arr[intI] = arr[intI - 1] + 1;
        }
    }

    int intN = n;
    while (intN > 1)
    {
        sequence.push_back(intN);

        if (intN % 3 == 0)
        {
            if (intN % 2 == 0)
            {
                if (arr[intN / 3] == arr[intN] - 1)
                {
                    intN = intN / 3;
                }
                else if (arr[intN / 2] == arr[intN] - 1)
                {
                    intN = intN / 2;
                }
                else
                {
                    intN -= 1;
                }
            }
            else
            {
                if (arr[intN / 3] == arr[intN] - 1)
                {
                    intN /= 3;
                }
                else
                {
                    intN -= 1;
                }
            }
        }
        else if (intN % 2 == 0)
        {
            if (arr[intN / 2] == arr[intN] - 1)
            {
                intN /= 2;
            }
            else
            {
                intN -= 1;
            }
        }
        else
        {
            intN -= 1;
        }
    }

    sequence.push_back(1);

    reverse(sequence.begin(), sequence.end());
    return sequence;
}

//----------------------------------------------------------------------------------------------------------------------
int main() 
{
    int n;
    std::cin >> n;
    vector<int> sequence = optimal_sequence(n);
    std::cout << sequence.size() - 1 << std::endl;
    for (size_t i = 0; i < sequence.size(); ++i) 
    {
        std::cout << sequence[i] << " ";
    }
}
//======================================================================================================================