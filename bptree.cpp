//
//  bptree.cpp
//  Database
//
//  Created by  魏小渺 on 2018/7/16.
//  Copyright © 2018年  魏小渺. All rights reserved.
//

#include "bptree.hpp"

Node:: Node(){
    id = 1;
    num = 0;
    isleaf = true;
    bro = -1;
}


Tree:: Tree(){
    root = new Node;
    scope = 1;
    start = 1;
    rID = 1;
}

void Tree:: writeNode(Node* node){
    fseek(this->file, sizeof(Node)*(node->id -1) + 2*sizeof(int), SEEK_SET);
    fwrite(node, sizeof(Node), 1, this->file);
}

void Tree:: readNode(Node* node, int id){
    fseek(this->file, (sizeof(Node))*(id - 1) + 2*sizeof(int), SEEK_SET);
    fread(node, sizeof(Node), 1, this->file);
}

void Tree:: initIndex(string tableName, string attr){
    Node* root_cpy = this->root;
    this->filename = tableName + "." + attr;
    char name_[100];
    for(int i = 0 ; i < 100; i++){
        if(i < this->filename.size()) name_[i] = this->filename[i];
        else name_[i] = '\0';
    }
    this->file = fopen(name_, "wb+");
    fwrite(&this->scope, sizeof(int), 1, this->file);
    fwrite(&this->rID, sizeof(int), 1, this->file);
    this->writeNode(root_cpy);
    //fclose(this->file);
    delete root_cpy;
    this->root = NULL;
}

void Tree:: indexToTree(){
    // I
}

void Tree:: insertNode_NF(Node *s, int k, unsigned int id){
    // AM
}

int Tree:: search(int k){
    // FUCKING 
}

void Tree:: insertKey(int k, int id){
    // DYSPHORIC
}

void Tree:: replaceKey(int oldkey, int newkey){
    // FOR
}

int Tree:: preDelete(Node* p, Node* x, unsigned int i){
    // THIS 
}

int Tree:: deleteKey_inNode(Node* p, int k){
    // FUCKING 
}

void Tree:: deleteKey(int k){
    // BPTREE
}
