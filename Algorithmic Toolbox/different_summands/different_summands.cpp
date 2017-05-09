#include <iostream>
#include <vector>

using namespace std;

//                                                          //AUTHOR:Hugo García
//                                                          //DATE: 4/23/2017
//                                                          //PURPOSE: Get the most different ints you can use to get
//                                                          //    the sum of n.

//======================================================================================================================
vector<int> optimal_summands(int n) 
{
    vector<int> arrintSummands;
    for (int intI = n, intJ = 1; intI > 0; intJ++) 
    {
        if (intI <= 2 * intJ) 
        {
            arrintSummands.push_back(intI);
            intI -= intI;
        } 
        else 
        {
            arrintSummands.push_back(intJ);
            intI -= intJ;
        }
    }
    return arrintSummands;
}

//----------------------------------------------------------------------------------------------------------------------
int main() 
{
    int n;
    std::cin >> n;
    vector<int> summands = optimal_summands(n);
    std::cout << summands.size() << '\n';
    for (size_t i = 0; i < summands.size(); ++i) 
    {
        std::cout << summands[i] << ' ';
    }
}
//======================================================================================================================