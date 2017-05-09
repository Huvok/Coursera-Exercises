#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

using namespace std;

//                                                          //AUTHOR:Hugo García
//                                                          //DATE: 4/23/2017
//                                                          //PURPOSE: Get the fewest numbers that are covered and
//                                                          //    covered all segments.

//======================================================================================================================
struct Segment 
{
    int start, end;
};

bool myfunction (Segment i,Segment j) 
{ 
    return (i.end < j.end); 
}

//----------------------------------------------------------------------------------------------------------------------
vector<int> optimal_points(vector<Segment> &segments) 
{
    vector<int> arrintPoints;
    sort(segments.begin(), segments.end(), myfunction);
    int current = segments[0].end;
    arrintPoints.push_back(current);

    for(int i = 0; i < segments.size(); i++) 
    {
        if (current < segments[i].start || 
            current > segments[i].end) 
        {
            current = segments[i].end;
            arrintPoints.push_back(current);
        }
    }

    return arrintPoints;
}

//----------------------------------------------------------------------------------------------------------------------
int main() 
{
    int n;
    std::cin >> n;
    vector<Segment> segments(n);

    for (size_t i = 0; i < segments.size(); ++i) 
    {
        std::cin >> segments[i].start >> segments[i].end;
    }

    vector<int> points = optimal_points(segments);
    std::cout << points.size() << "\n";

    for (size_t i = 0; i < points.size(); ++i) 
    {
        std::cout << points[i] << " ";
    }
}
//======================================================================================================================