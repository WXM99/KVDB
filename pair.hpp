//
//  pair.hpp
//  Database
//
//  Created by  魏小渺 on 2018/7/16.
//  Copyright © 2018年  魏小渺. All rights reserved.
//

#ifndef pair_hpp
#define pair_hpp

#include <string>
#include <stdio.h>

using namespace std;
class Pair{
public:
    static int total;
    int pos;
    string id;
    string contains;
    Pair();
    Pair(int pos);
};


#endif /* pair_hpp */
