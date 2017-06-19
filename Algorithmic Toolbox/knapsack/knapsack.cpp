#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//                                                          //AUTHOR: Hugo García
//                                                          //DATE: 5/18/2017
//                                                          //PURPOSE: DP Knapsack problem with no repetitions.

//======================================================================================================================
int arr[301][10001];

int optimal_weight(int W, const vector<int> &w) 
{   
    for (int intI = 0; intI <= w.size(); ++intI)
    {
        for (int intJ = 0; intJ <= W; ++intJ)
        {
            if (intI == 0 || intJ == 0)
            {
                arr[intI][intJ] = 0;
            }
            else if (w[intI - 1] <= intJ)
            {
                arr[intI][intJ] = max(arr[intI - 1][intJ], arr[intI - 1][intJ - w[intI - 1]] + w[intI - 1]);
            }
            else
            {
                arr[intI][intJ] = arr[intI - 1][intJ];
            }
        }
    }

    return arr[w.size()][W];
}

//----------------------------------------------------------------------------------------------------------------------
int main() 
{
    int n, W;
    std::cin >> W >> n;
    vector<int> w(n);
    for (int i = 0; i < n; i++) 
    {
        std::cin >> w[i];
    }

    std::cout << optimal_weight(W, w) << '\n';
}
//======================================================================================================================