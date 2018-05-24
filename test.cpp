//
//  test.cpp
//  project5
//
//  Created by Ryan Schmied on 2018-04-04.
//  Copyright © 2018 Ryan Schmied. All rights reserved.
//

#include <iostream>
#include "Weighted_graph_tester.h"
using namespace std;
int main() {
    Weighted_graph test(25);
    
    test.insert(0,1,1.0);
    test.insert(0,6,2.5);
    test.insert(0,3,1.5);
    test.insert(1,2,2.5);
    test.insert(3,4,1.5);
    test.insert(2,5,4.5);
    test.insert(6,11,3.6);
    test.insert(4,8,1.5);
    test.insert(4,5,3.0);
    test.insert(7,8,1.5);
    test.insert(7,10,1.5);
    test.insert(10,11,1.5);
    test.insert(10,9,2.0);
    test.insert(10,13,2.5);
    test.insert(11,12,1.5);
    test.insert(10,12,3.5);
    test.insert(12,17,4.0);
    test.insert(12,16,1.5);
    test.insert(16,14,3.5);
    test.insert(16,23,1.5);
    test.insert(16,19,3.0);
    test.insert(19,18,4.5);
    test.insert(18,20,1.5);
    test.insert(21,24,5.0);
    test.insert(21,22,1.0);
    test.insert(22,24,3.0);
    
    cout<<test.distance(0,23);
}
