//
//  datafile.cpp
//  Database
//
//  Created by  魏小渺 on 2018/7/17.
//  Copyright © 2018年  魏小渺. All rights reserved.
//

#include "datafile.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

void Pair:: setTotal(int lastPos){
    total = lastPos;
}

Pair:: Pair(){
    total++;
    pos = total;
    readnext = 0;
}

Pair:: Pair(int pos){
    this->pos = pos;
    readnext = 0;
}

Pair:: Pair(int key, string value){
    this->id = key; 
    for(int i = 0; i < S; i++){
        if(i < value.size() )this->contains[i] = value[i];
        else this->contains[i] = '\0';
    }
    this->pos = 0;
    readnext = 0;
}
//=========================================
//=========================================
Data:: Data(){
    this->datafile = NULL;
    Pair* clear = new Pair(0);
    clear->setTotal(0);
}

void Data:: creatDataFile(string path){
    path = path +".dat";
    char path_[100];
    string_to_char(path_, path);
    this->datafile = fopen(path_,"wb+");
}

int Data:: openDataFile(string path){
    path = path +".dat";
    ifstream test;
    test.open(path);
    if(test.good()){
        char path_[100];
        string_to_char(path_, path);
        this->datafile = fopen(path_,"rb+");
        return 0;
    }else{
        return -1;
    }
}

void Data:: closeDataFile(){
    this->flush();
    fclose(this->datafile);
}

void Data:: readData(Pair *pair,int pos){
    fseek(this->datafile, (sizeof(Pair)*(pos  -1)),SEEK_SET);
    fread(pair, sizeof(Pair), 1, this->datafile);
}

void Data:: writeData(Pair *pair){
    fseek(this->datafile, sizeof(Pair)*(pair->pos-1),SEEK_SET);
    fwrite(pair,sizeof(Pair), 1, this->datafile);
}

void Data:: insertPair(int id, string contains){
    Pair* e = new Pair;
    //string_to_char(e->id,id);
    e->id = id ;
    string_to_char(e->contains,contains);
    Pair cpy = *e;
    this->putInBf(cpy);
    delete e;
}

void Data:: insertPair(int id, char contains[S]){
    Pair* e = new Pair;
    e->id = id;
    string_to_char(e->contains,contains);
    Pair cpy = *e;
    this->putInBf(cpy);
    delete e;
}
void Data:: insertPair(int pos, int id, string contains){
    Pair* e = new Pair(pos);
    //string_to_char(e->id,id);
    e->id = id ;
    string_to_char(e->contains,contains);
    Pair cpy = *e;
    this->putInBf(cpy);
    delete e;
}

void Data:: deletePair(int pos){
    if(this->Buffer.size() <= 1){
        this->Buffer.clear();
    }else{
        vector<Pair> :: iterator it;
        for(it = this->Buffer.begin(); it != this->Buffer.end(); it++){
            if( (it) -> pos == pos && Buffer.size() != 1)
                this->Buffer.erase(it);
        }
    }
}

Pair Data:: seekPair(int pos){
    Pair local = Pair(pos);
    if(pos > 0){
        
        for(int i = 0; i < this->Buffer.size();i++){
            // seaching in buffer
            
            Pair t = this->Buffer[i];
            if(t.pos == pos){
                return t;
            }
        }
        
        Pair* tar = new Pair(pos);
        this->readData(tar, pos);
        for(int i = 0; i<100; i++){
            local.contains[i] = tar->contains[i];
        }
        local.id = tar->id;
        delete tar;
    }
    return local;
}

void Data:: replacePair(int pos,int key,string value){
    char value_char[100];
    string_to_char(value_char, value);
    
    Pair* newPair = new Pair(pos);
    newPair->id = key;
    for(int i = 0; i < 100; i++){
        newPair->contains[i] = value_char[i];
    }
    
    int i = 0;
    for(i = 0; i < this->Buffer.size() ; i++){
        if(this->Buffer[i].pos == pos) break;
    }
    
    if(this->Buffer[i].pos == pos) this->Buffer[i] = *newPair;
    else this->putInBf(*newPair);
    
    delete newPair;
}

int Data:: string_to_int(string input){
    stringstream tmp;
    tmp << input;
    int res;
    tmp >> res;
    return res;
}

void Data:: string_to_char(char* ch, string input){
    for(int i = 0; i < 100; i++){
        if(i < input.size()) ch[i] = input[i];
        else ch[i] = '\0';
    }
}

void Data:: putInBf(Pair a){
    this->Buffer.push_back(a);
    if(this->Buffer.size() == BfLimit){
        this->flush();
    }
}

void Data::flush(){
    while (!this->Buffer.empty()) {
        Pair a = this->Buffer.back();
        this->Buffer.pop_back();
        this->writeData(&a);
    }
    fflush(this->datafile);
}

