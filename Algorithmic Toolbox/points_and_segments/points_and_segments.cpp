#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

//                                                          //AUTHOR: Hugo García
//                                                          //DATE: 5/1/2017
//                                                          //PURPOSE: Count the number segments that include each 
//                                                          //    point.

//======================================================================================================================
struct Segment
{
    int intX, intY;
};

//----------------------------------------------------------------------------------------------------------------------
bool boolSortByX (Segment i,Segment j) { return (i.intX < j.intX); }

//----------------------------------------------------------------------------------------------------------------------
bool boolSortByY (Segment i,Segment j) { return (i.intY < j.intY); }

//----------------------------------------------------------------------------------------------------------------------
int intBinarySearchByX(vector<Segment> lstSegment, int intLeft, int intRight, int intPoint) 
{
    int intPosition = -1;
    while (intLeft <= intRight) 
    {
        if (intLeft == intRight) 
        {
            Segment segment = lstSegment[intLeft];
            if (segment.intX <= intPoint) 
            {
                intPosition = intLeft;
            }

        break;
        }

        int intMiddle = intLeft + ((intRight - intLeft) / 2);
        Segment segment = lstSegment[intMiddle];

        if (segment.intX <= intPoint) 
        {
            intPosition = intMiddle;
            intLeft = intMiddle + 1;
        } 
        else if (segment.intX > intPoint) 
        {
            intRight = intMiddle;
        }
    }

    return intPosition;
}

//----------------------------------------------------------------------------------------------------------------------
int intBinarySearchByY(vector<Segment> lstSegment, int intLeft, int intRight, int intPoint) 
{
    if (lstSegment.empty()) 
    {
        return -1;
    }

    if (intLeft == intRight) 
    {
        return lstSegment[intLeft].intY >= intPoint ? intLeft : -1;
    }

    int intMiddle = intLeft + ((intRight - intLeft) / 2);

    Segment segment = lstSegment[intMiddle];
    if (segment.intY >= intPoint) 
    {
        return intBinarySearchByY(lstSegment, intLeft, intMiddle, intPoint);
    } 
    else 
    {
        return intBinarySearchByY(lstSegment, intMiddle + 1, intRight, intPoint);
    }
}

//----------------------------------------------------------------------------------------------------------------------
vector<int> arrintCount(vector<Segment> lstSegment, vector<int> lstPoints) 
{
    vector<int> lstCount(lstPoints.size());

    sort(lstSegment.begin(), lstSegment.end(), boolSortByX);
    for (int intI = 0; intI < lstPoints.size(); intI++) 
    {
        int intPosition = intBinarySearchByX(lstSegment, 0, lstSegment.size() - 1, lstPoints[intI]);
        if (intPosition != -1) 
        {
            vector<Segment> arrLeftToSearch(intPosition + 1);

            for(size_t i = 0; i < intPosition + 1; ++i) 
            {
                arrLeftToSearch[i].intX = lstSegment[i].intX;
                arrLeftToSearch[i].intY = lstSegment[i].intY;
            }

            sort(lstSegment.begin(), lstSegment.end(), boolSortByY);

            intPosition = intBinarySearchByY(arrLeftToSearch, 0, arrLeftToSearch.size() - 1, lstPoints[intI]);

            lstCount[intI] = intPosition != -1 ? arrLeftToSearch.size() - intPosition : 0;

        } 
        else
        {
            lstCount[intI] = 0;
        }
    }

    return lstCount;
}

//----------------------------------------------------------------------------------------------------------------------
int main() 
{
    int intN, intM, intX, intY;
    std::cin >> intN >> intM;
    vector<Segment> lstSegment(intN);
    for (size_t i = 0; i < intN; i++) 
    {
        std::cin >> intX >> intY;
        lstSegment[i].intX = intX;
        lstSegment[i].intY = intY;
    }

    vector<int> points(intM);
    for (size_t i = 0; i < points.size(); i++) 
    {
        std::cin >> points[i];
    }

    vector<int> cnt = arrintCount(lstSegment, points);
    for (size_t i = 0; i < cnt.size(); i++) 
    {
        std::cout << cnt[i] << ' ';
    }
}
//======================================================================================================================