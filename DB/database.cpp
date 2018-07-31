//
//  database.cpp
//  Database
//
//  Created by  魏小渺 on 2018/7/16.
//  Copyright © 2018年  魏小渺. All rights reserved.
//

#include "database.hpp"
#include <sstream>
#include <fstream>

DB:: DB(){
    this->myTree = new Tree();
    this->myData = new Data();
    this->myCache = new Cache();
    this->myHolder = new Holder();
}

void DB:: create(string path){
    this->myData->creatDataFile(path);
    this->myTree->initIndex(path);
}

void DB::IOcreate(){
    string path;
    cout << "Enter the new project name: ";
    cin >> path;
    cout << "Building database..." <<endl;
    this->create(path);
    cout << "An empty DB "<< path << " has been built." <<endl;
}


bool DB:: open(string path){
    int exist = this->myData->openDataFile(path);
    if(exist < 0) return false;
    else{
        string keeper = path + ".kpt";
        ifstream tmp;
        tmp.open(keeper);
        int lastPos;
        tmp >> lastPos;
        Pair* keep = new Pair(lastPos);
        keep->setTotal(lastPos);
        
        this->myData->openDataFile(path);
        this->myTree->openIndex(path);
        
        return true;
    }
}
void DB::IOopen(){
    string path;
    cout << "Enter the project name: ";
    cin >> path;
    if(!this->open(path)){
        cout << "No such project." <<endl;
        cout << "Do you want to creat a new project("
        << path <<")?(Y or N): ";
        string creat_new;
        cin >> creat_new;
        if(creat_new[0] == 'Y' || creat_new[0] == 'y'){
            this->create(path);
            cout << "An empty DB "<< path
            << " has been built." <<endl;
        }else{
            this->IOopen();
        }
    }else{
        cout << path <<" opened."<<endl;
    }
}


void DB::insert(int key, string value){
    
    int newPosition;
    if(this->myHolder->empty()){
        this->myData->insertPair(key, value);
        int current_scope = Pair:: total;
        newPosition = current_scope;
        this->myTree->insertKey(key, newPosition);
    }else{
        Pair rmd = this->myHolder->pop();
        newPosition = rmd.pos;
        this->myData->insertPair(newPosition, key, value);
        this->myTree->replaceKey(key, rmd.id);
    }
    
    this->myCache->put(key, value);
}

void DB::IOinsert(){
    string value;
    int key;
    cout << "<I>Enter key: ";
    cin >> key;
    string val = this->myCache->search(key);
    if(val != ""){
        cout <<"key: "<< key <<" has been in DB."<<endl;
    }else{
        int pos = this->search(key);
        if(pos > 0) {
            cout <<"key: "<< key <<" has been in DB."<<endl;
        }else{
            cout << "<I>Enter value: ";
            cin >> value;
            this->insert(key, value);
            cout <<"< "<<key<<" - "<<value
            <<" >\nhas been inserted."<<endl;
        }
    }
}


Pair DB:: get(int key){
    string val = this->myCache->search(key);
    if(val != ""){
        Pair b = Pair(key, val);
        b.pos = 1;
        return b;
    }else{
        int pos = this->search(key);
        Pair sub = this->myData->seekPair(pos);
        if(sub.pos > 0) this->myCache->put(sub.id, sub.contains);
        return sub;
    }
}


void DB::IOget(){
    cout << "<S>Enter the key: ";
    int input;
    cin >> input;
    Pair tar = this->get(input);
    if(tar.pos > 0){
        cout << "key: "<<tar.id<<endl;
        cout << "value: "<<tar.contains<<endl;
    }
    else cout << "Could not find key: "<< input
        << " in DB." << endl;
}


vector<Pair> DB:: rangeGet(int k1, int k2){
    vector<Pair> store;
    for(int i = k1; i <= k2; i++){
        int pos = this->search(i);
        if(pos > 0){
            Pair valid = this->myData->seekPair(pos);
            store.push_back(valid);
        }
        if(store.size() == Pair::total) break;
    }
    return store;
}

void DB::IOrangeGet(){
    cout << "Range from:\n>> ";
    int k1;
    cin >> k1;
    cout << "To:\n>> ";
    int k2;
    cin >> k2;
    vector<Pair> datas = this->rangeGet(k1, k2);
    if(datas.size() == 0)
        cout <<"No keys in this range."<<endl;
    else{
        for(int i = 0; i<datas.size(); i++){
            cout << "key: "<<datas[i].id<<endl;
            cout << "value: "<<datas[i].contains<<endl;
        }
    }
}


int DB::remove(int key){
    
    Pair tar = this->get(key);
    this->myCache->remove(key);
    int pos = tar.pos;
    if(pos < 0) return -1;
    else{
        this->myHolder->put(tar);
        this->myData->deletePair(pos);
        this->myTree->deleteKey(key);
        return pos;
    }
}

void DB:: IOremove(){
    cout << "<R>Ender key: ";
    int id;
    cin >> id;
    if(this->remove(id) == -1){
        cout << id <<" is not found in DB." <<endl;
    }else{
        cout << id << " has been deleted."<<endl;
    }
}

void DB::replace(int pos, int key, string value){
    this->myData->replacePair(pos, key, value);
    this->myCache->remove(key);
    this->myCache->put(key, value);
}

void DB::IOreplace(){
    cout << "Ender the key should be replaced: ";
    int key;
    cin >> key;
    Pair tar = this->get(key);
    if(tar.pos < 0){
        cout << "no this key: "<< key <<" in DB." <<endl;
    }else{
        cout << "Ender the value should be replaced: ";
        string value;
        cin >> value;
        this->replace(tar.pos, key, value);
        cout << "replace successfully!" <<endl;
    }
}

void DB:: keepPos(string name){
    while(name[name.size()-1] != '.'){
        name.pop_back();
    }
    name += "kpt";
    ofstream tmp;
    tmp.open(name);
    int lastPos = Pair:: total ;
    
    tmp << lastPos;
    
    tmp.close();
}

void DB:: save(){
    string name = this->myTree->filename;
    if(!name.empty()){
        this->keepPos(name);
        this->myData->closeDataFile();
        this->myTree->closeIndex();
    }else{
    }
}

void DB:: BigSize(int size,char contains[S]){
    clock_t st = clock();
    for(int i = 0; i <= size; i++){
        this->myData->insertPair(i, contains);
        int current_scope = Pair:: total;
        int newPosition = current_scope;
        this->myTree->insertKey(i, newPosition);
    }
    cout << "consuming: " << clock()-st  << " μs" <<endl;
}


int DB:: search(int key){
    int pos = this->myTree->searchPos(key);
    return pos;
}
