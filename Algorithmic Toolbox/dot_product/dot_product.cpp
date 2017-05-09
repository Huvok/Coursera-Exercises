#include <algorithm>
#include <iostream>
#include <vector>

//                                                          //AUTHOR:Hugo García
//                                                          //DATE: 4/23/2017
//                                                          //PURPOSE: Get the best profit from a set of items with
//                                                          //      different values and weights

using std::vector;

//======================================================================================================================
long long max_dot_product(vector<int> a, vector<int> b) 
{
    long long longResult = 0;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    for (size_t i = 0; i < a.size(); i++) 
    {
        longResult += ((long long) a[i]) * b[i];
    }
    return longResult;
}

//----------------------------------------------------------------------------------------------------------------------
int main() 
{
    size_t n;
    std::cin >> n;
    vector<int> a(n), b(n);
    for (size_t i = 0; i < n; i++) 
    {
    std::cin >> a[i];
    }

    for (size_t i = 0; i < n; i++) 
    {
    std::cin >> b[i];
    }

    std::cout << max_dot_product(a, b) << std::endl;
}
//======================================================================================================================