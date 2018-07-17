//
//  bptree.hpp
//  Database
//
//  Created by  魏小渺 on 2018/7/16.
//  Copyright © 2018年  魏小渺. All rights reserved.
//

#ifndef bptree_hpp
#define bptree_hpp


//#include "pair.hpp"
#include <string>
#include <stdio.h>
#include <iostream>

#define M 40
using namespace std;

class Node{
public:
    unsigned int id;
    unsigned int num;
    bool isleaf;
    int keys[2*M];
    int sons[2*M];
    int bro;
    Node();
    
};

class Tree{
public:
    Node* root;
    unsigned int rID;
    unsigned int scope;
    string filename;
    FILE* file;
    int start;
    Tree();
    void writeNode(Node*);
    void readNode(Node*, int id);
    void initIndex(string, string);
    void indexToTree();
    void splitNode(Node* p, Node* c, int i);
    void insertNode_NF(Node*s, int key, unsigned int id);
    
    int  search(int key);
    
    void insertKey(int key, int id);
    void replaceKey(int oldkey, int newkey);
    int preDelete(Node*,Node*,unsigned int);
    int deleteKey_inNode(Node*, int key);
    void deleteKey(int key);
};

#endif /* bptree_hpp */
