#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

//                                                          //AUTHOR: Hugo García
//                                                          //DATE: 5/18/2017
//                                                          //PURPOSE: Get the minimum edit distance between two
//															//		strings.

//======================================================================================================================
int min(int x, int y, int z)
{
    return min(min(x, y), z);
}

//----------------------------------------------------------------------------------------------------------------------
int edit_distance(const string &str1, const string &str2, int m, int n) 
{
	int arr[m + 1][n + 1];
 
    for (int intI = 0; intI <= m; intI++)
    {
        for (int intJ = 0; intJ <= n; intJ++)
        {
            if (intI == 0)
                arr[intI][intJ] = intJ;
            else if (intJ == 0)
                arr[intI][intJ] = intI;
            else if (str1[intI-1] == str2[intJ-1])
                arr[intI][intJ] = arr[intI-1][intJ-1];
            else
                arr[intI][intJ] = 1 + min(arr[intI][intJ-1],  // Insert
                                   arr[intI-1][intJ],  // Remove
                                   arr[intI-1][intJ-1]); // Replace
        }
    }
 
    return arr[m][n];
}

//----------------------------------------------------------------------------------------------------------------------
int main() 
{
	string str1;
	string str2;
	cin >> str1 >> str2;
	std::cout << edit_distance(str1, str2) << std::endl;
	return 0;
}
//======================================================================================================================