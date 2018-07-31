//
//  CacheAndHolder.hpp
//  Database9
//
//  Created by  魏小渺 on 2018/7/24.
//  Copyright © 2018年 weixm. All rights reserved.
//

#ifndef CacheAndHolder_hpp
#define CacheAndHolder_hpp

#include <stdio.h>
#include <string>
#include <queue>
#include <iostream>

#include "../data/datafile.hpp"
#define CacSize 1
using namespace std;


class CacheNode{
public:
    CacheNode();
    int key;
    string value;
    CacheNode* next;
    CacheNode* last;
};

class Cache{
public:
    Cache();
    void put(int k, string v);
    string search(int key);
    void clear();
    void remove(int key);
    int size;
private:
    CacheNode* root;
    CacheNode* tail;
    int limit;
};
//===============================
class Holder{
public:
    void put(Pair rmd);
    Pair pop();
    bool empty();
    queue<Pair> posHolder;
};
//===============================
#endif /* CacheAndHolder_hpp */
