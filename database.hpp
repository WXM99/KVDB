//
//  database.hpp
//  Database
//
//  Created by  魏小渺 on 2018/7/16.
//  Copyright © 2018年  魏小渺. All rights reserved.
//

#ifndef database_hpp
#define database_hpp

#include "pair.hpp"
#include "bptree.hpp"
#define datapath "./datafile.dat"

class DB{
public:
    DB();
    
    void creat_dataFile();
    void close_dataFile();
    
    void readData(Pair* pair, int pos);
    void writeData(Pair* pair);
    
    void insert_pair(string id, string contains);
    void delete_pair(int pos);
    void print_pair(int pos);
    
    int string_to_int(string input);
    
    void creat();
    void insert();
    void search();
    void remove();
    void close();
    
private:
    Tree* mytree;
    FILE* datafile;
};


#endif /* database_hpp */
