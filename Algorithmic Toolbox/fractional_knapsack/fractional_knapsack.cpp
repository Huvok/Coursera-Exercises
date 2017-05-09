#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

//                                                          //AUTHOR:Hugo García
//                                                          //DATE: 4/23/2017
//                                                          //PURPOSE: Get the best profit from a set of items with
//                                                          //      different values and weights
  
using namespace std;
using std::vector;

//======================================================================================================================
class Item
{
public:
    int value, weight;
 
    Item(int value, int weight)
    {
        this->value = value;
        this->weight = weight;
    }

    Item()
    {
        this->value = 0;
        this->weight = 0;
    }
};

bool cmp(Item a, Item b)
{
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

//======================================================================================================================
double get_optimal_value(int capacity, vector<Item> arr, int n) 
{
    sort(arr.begin(), arr.end(), cmp);

    int curWeight = 0;
    double finalvalue = 0.0;

    //Looping through all Items
    for (int i = 0; i < n; i++)
    {
        //If adding Item won't overflow, add it completely
        if (curWeight + arr[i].weight <= capacity)
        {
            curWeight += arr[i].weight;
            finalvalue += arr[i].value;
        }
        //If we can't add current Item, add fractional part of it
        else
        {
            int remain = capacity - curWeight;
            finalvalue += arr[i].value * ((double) remain / arr[i].weight);
            break;
        }
    }

    return finalvalue;
}

int main() 
{
    int intN;
    int intCapacity;
    std::cin >> intN >> intCapacity;
    vector<int> values(intN);
    vector<int> weights(intN);
    vector<Item> arr;
    for (int i = 0; i < intN; i++) 
    {
        std::cin >> values[i] >> weights[i];
        Item item;
        item.value = values[i];
        item.weight = weights[i];
        arr.push_back(item);
    }

    double optimal_value = get_optimal_value(intCapacity, arr, values.size());

    std::cout.precision(10);
    std::cout << optimal_value << std::endl;
    return 0;
}
//======================================================================================================================