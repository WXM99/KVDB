//
//  database.hpp
//  Database
//
//  Created by  魏小渺 on 2018/7/16.
//  Copyright © 2018年  魏小渺. All rights reserved.
//

#ifndef database_hpp
#define database_hpp

#include "./data/datafile.hpp"
#include "./tree/bptree.hpp"
#include "./tools/CacheAndHolder.hpp"


/* class DB
 * --------------------------------------
 * Database resembles class Tree and Data
 */

class DB{
public:
    
    // constructor
    DB();
    
    // give the position in data through a key
    int search(int key);
    
    // creat empty datafile and indexfile
    // function with prefix "IO" means IO is assembled
    void create(string path);
    void IOcreate();
    
    // open datafile and indexfile made by this program
    bool open(string path);
    void IOopen();
    
    // creat pos keeper file
    void save();
    
    // insert a key in db
    void insert(int key, string value);
    void IOinsert();
    
    // find a certain pair whose id is key
    Pair get(int key);
    void IOget();
    
    // find pairs in a key range
    vector<Pair> rangeGet(int k1, int k2);
    void IOrangeGet();
    
    // delete a key and its value in data and index file
    int  remove(int key);
    void IOremove();
    
    // change the value of a pair whose id is a given key
    void replace(int pos, int key, string value);
    void IOreplace();
    
    // init a big DB with given number and value
    void BigSize(int size, char contains[S]);
    
    // creat a pos keeper file
    void keepPos(string path);

    
private:
    
    // index manager
    Tree* myTree;
    
    // data manager
    Data* myData;
    
    // tool: Cahche
    Cache* myCache;
    
    // tools: Holder
    Holder* myHolder;
    
};


#endif /* database_hpp */
