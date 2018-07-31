//
//  datafile.hpp
//  Database
//
//  Created by  魏小渺 on 2018/7/17.
//  Copyright © 2018年  魏小渺. All rights reserved.
//

#ifndef datafile_hpp
#define datafile_hpp

#include <stdio.h>
#include <string>
#include <vector>
#define S 100
#define BfSize 1
using namespace std;


/* class Pair
 * -------------------------------
 * A basic structure in class Data;
 */
class Pair{
public:
    
    // constructor using counter total
    Pair();
    
    // constructot without using total
    Pair(int pos);
    Pair(int key, string value);
    
    // an auto-conter to get position
    static int total;
    
    // change the counter above manually
    void setTotal(int lastPos);
    
    // {pos} is the position of pair in datafile
    // differs from pos in tree node
    // this pos is the order a data come in
    // pos in tree node is the address of node
    // the two poses are not the same except #1
    // for a tree node may contains one more data(surely)
    int pos;
    
    // key in char*
    int id;
    
    // value in char*
    char contains[S];
    
    int readnext;
    
};


/* class Data
 * -------------------------------
 * A class managing datafile
 */
class Data{
public:
    
    // constructor
    Data();
    
    // creat an empty datafile
    void creatDataFile(string path);
    
    // open an datafile created by this program
    int  openDataFile(string path);
    
    // close the data file
    void closeDataFile();
    
    // insert a pair into datafile
    void insertPair(int id, string contains);
    void insertPair(int id, char contains[S]);
    // inserting at a given pos
    void insertPair(int pos, int id,  string contains);
    
    
    // delete a pair in the given position
    void deletePair(int pos);
    
    // give out the info of pos pair through a copy one
    Pair seekPair(int pos);
    
    // change the info of a pair in a given position
    //void replacePair(int pos,string key, string value);
    void replacePair(int pos, int key, string value);
    
private:
    
    
    // store <key-value>pair compactly
    FILE* datafile;
    
    // make pair* just the same as pos pair in datafile
    void readData(Pair* pair, int pos);
    
    // write pair in to datafile in pos of pair->pos
    void writeData(Pair* pair);
    
    // helper funcs to fit C style FILE*
    int string_to_int(string input);
    void string_to_char(char* ch, string input);
    
    
    
    // Tools buffer.
    vector<Pair> Buffer;
    const int BfLimit = BfSize;
    Pair searchInBf(int pos);
    void putInBf(Pair a);
    void flush();
    
    
};



#endif /* datafile_hpp */
