#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <float.h>

using std::vector;
using std::string;
using std::pair;
using std::min;

//                                                          //AUTHOR: Hugo García
//                                                          //DATE: 5/1/2017
//                                                          //PURPOSE: Find the closest pair of points in 2D.

//======================================================================================================================
struct Point
{
    int intX, intY;
};

//----------------------------------------------------------------------------------------------------------------------
int compareX(const void* a, const void* b)
{
    Point *p1 = (Point *)a,  *p2 = (Point *)b;
    return (p1->intX - p2->intX);
}

//----------------------------------------------------------------------------------------------------------------------
int compareY(const void* a, const void* b)
{
    Point *p1 = (Point *)a,   *p2 = (Point *)b;
    return (p1->intY - p2->intY);
}

//----------------------------------------------------------------------------------------------------------------------
double numGetDistance(Point p1, Point p2)
{
    return sqrt((p1.intX - p2.intX)*(p1.intX - p2.intX) +
                (p1.intY - p2.intY)*(p1.intY - p2.intY)
                );
}

//----------------------------------------------------------------------------------------------------------------------
double doubleGetClosest(Point lstPoint[], int intN)
{
    double numMin = DBL_MAX;
    for (int i = 0; i < intN; ++i)
    {
        for (int j = i + 1; j < intN; ++j)
        {
            if (numGetDistance(lstPoint[i], lstPoint[j]) < numMin)
            {
                numMin = numGetDistance(lstPoint[i], lstPoint[j]);
            }
        }
    }
    return numMin;
}

//----------------------------------------------------------------------------------------------------------------------
double numGetClosestInStrip(Point arrpoint[], int intSize, double numDistance)
{
    double numMin = numDistance;
 
    qsort(arrpoint, intSize, sizeof(Point), compareY); 
 
    for (int i = 0; i < intSize; ++i)
    {
        for (int j = i + 1; j < intSize && (arrpoint[j].intY - arrpoint[i].intY) < numMin; ++j)
        {
            if (numGetDistance(arrpoint[i], arrpoint[j]) < numMin)
            {
                numMin = numGetDistance(arrpoint[i], arrpoint[j]);
            }
        }
    }
 
    return numMin;
}

//----------------------------------------------------------------------------------------------------------------------
double numFindClosestPair(Point lstPoint[], int intN)
{
    if (intN <= 3)
    {
        return doubleGetClosest(lstPoint, intN);
    }

    int intMiddle = intN / 2;
    Point pointMiddle = lstPoint[intMiddle];
 
    double numMinLeft = numFindClosestPair(lstPoint, intMiddle);
    double numMinRight = numFindClosestPair(lstPoint + intMiddle, intN - intMiddle);
 
    double numMin = min(numMinLeft, numMinRight);
 
    Point arrpoint[intN];
    int j = 0;
    for (int i = 0; i < intN; i++)
    {
        if (abs(lstPoint[i].intX - pointMiddle.intX) < numMin)
        {
            arrpoint[j] = lstPoint[i];
            j++;
        }
    }
 
    return min(numMin, numGetClosestInStrip(arrpoint, j, numMin));
}

//----------------------------------------------------------------------------------------------------------------------
int main() 
{
    size_t intN;
    int intX, intY;
    std::cin >> intN;
    Point lstPoint[intN];
    for (size_t i = 0; i < intN; i++) 
    {
        std::cin >> intX >> intY;
        lstPoint[i].intX = intX;
        lstPoint[i].intY = intY;
    }

    qsort(lstPoint, intN, sizeof(Point), compareX);

    std::cout << std::fixed;
    std::cout << std::setprecision(9) << numFindClosestPair(lstPoint, intN) << "\n";
}
//======================================================================================================================