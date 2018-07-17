//
//  database.cpp
//  Database
//
//  Created by  魏小渺 on 2018/7/16.
//  Copyright © 2018年  魏小渺. All rights reserved.
//

#include "database.hpp"
#include <sstream>
DB:: DB(){
    this->mytree = new Tree();
}

void DB:: creat_dataFile(){
    this->datafile = fopen(datapath,"wb+");
}

void DB:: close_dataFile(){
    fclose(this->datafile);
}

void DB:: readData(Pair *pair,int pos){
    //this->datafile = fopen(datapath,"rb+");
    fseek(this->datafile, (sizeof(Pair)*(pos -1)),SEEK_SET);
    fread(pair, sizeof(Pair), 1, this->datafile);
    //fclose(this->datafile);
}

void DB:: writeData(Pair *pair){
    //this->datafile = fopen(datapath,"wb");
    fseek(this->datafile, sizeof(Pair)*(pair->pos-1),SEEK_SET);
    fwrite(pair,sizeof(Pair), 1, this->datafile);
    //fclose(this->datafile);
}

void DB:: insert_pair(string id, string contains){
    Pair* e = new Pair;
    e->id = id; 
    e->contains = contains;
    this->writeData(e);
    delete e;
}

void DB:: delete_pair(int pos){
    Pair* b = new Pair(pos);
    memset(b,' ',sizeof(Pair));
    b->pos = pos;
    b->contains[20] = '\n';
    this->writeData(b);
    delete b;
}

void DB:: print_pair(int pos){
    Pair* b = new Pair(pos);
    this->readData(b, pos);
    cout << "<S>key: " << b->id << endl;
    cout << "<S>value: " << b->contains <<endl;
    delete b;
}

int DB:: string_to_int(string input){
    stringstream tmp;
    tmp << input;
    int res;
    tmp >> res;
    return res;
}

void DB:: creat(){
    cout << "Building database..." <<endl;
    this->creat_dataFile();
    this->mytree->initIndex("index", "idx");
    this->mytree->indexToTree();
    cout << "An empty DB has been built." <<endl;
}

void DB:: insert(){
    string id, value;
    cout << "<I>Enter key: ";
    cin >> id;
    cout << "<I>Enter value: ";
    cin >> value;
    int key = string_to_int(id);
    if(this->mytree->search(key) > 0){
        cout << "<I>Key:" << key << " has been in DB." << endl;
    }else{
        this->insert_pair(id, value);
        int all = Pair:: total;
        this->mytree->insertKey(key, all);
        cout <<"<"<<id<<"-"<<value<<"> has been iserted."<<endl;
    }
}

void DB:: search(){
    cout << "<S>Enter the key: ";
    string input;
    cin >> input;
    int key = string_to_int(input);
    int pos = this->mytree->search(key);
    if(pos > 0){
        print_pair(pos);
    }else{
        cout << "Could not find key: "<< key << "in DB." << endl;
    }
}

void DB:: remove(){
    cout << "<R>Ender key: ";
    string id;
    cin >> id;
    int key = string_to_int(id);
    int pos = this->mytree->search(key);
    if(pos < 0){
        cout << id <<"is not found in DB." <<endl;
    }else{
        this->delete_pair(pos);
        this->mytree->deleteKey(key);
        cout << id << "has been deleted."<<endl;
    }
}

void DB:: close(){
    fclose(this->datafile);
}
