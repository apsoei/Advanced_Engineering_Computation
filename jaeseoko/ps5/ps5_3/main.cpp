#include <iostream>
#include "bintree.h"
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

// Test Last and FindPrev functions.


int main(void)
{
    int last = 0;
    BinaryTree <int,int> tree;
    BinaryTree <int,int>::NodeHandle ndHd;
    srand((int)time(nullptr));
    int size = 100;
    std::vector <int> vec;
    for(int i=0; i<size; ++i)
    {
        int randN = rand()%100;
        tree.Insert(randN,0);
    }

    ndHd = tree.Last();
    last = tree.GetKey(ndHd);

    vec.push_back(last);

    for(;;)
    {
        ndHd = tree.FindPrev(ndHd);
        if(ndHd.IsNull()) break;
        vec.push_back(tree.GetKey(ndHd));
    }
    
    // CHECK vector size == input number size
    if(vec.size()!= size)
    {
        std::cout << "size not match" <<std::endl;
        return 1;
        
    }
    // CHECK max of numbers == last
    if(* std::max_element(vec.begin(),vec.end())!=last)
    {
        std::cout << "Last(max) value not match" <<std::endl;
        return 1;
        
    }
    // CHECK vector is in descending order
    for(int i=0; i<vec.size()-1; ++i)
    {
        // Next number can be less than or equal to current one, but CANNOT be greater.
        // If greater, throw out error.
        if(vec[i]<vec[i+1])
        {
            std::cout << "Prev function failed" <<std::endl;
            return 1;
        }
    }

    std::cout << "test passed"<<std::endl;
    return 0;
}