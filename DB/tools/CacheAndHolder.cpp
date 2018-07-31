//
//  CacheAndHolder.cpp
//  Database9
//
//  Created by  魏小渺 on 2018/7/24.
//  Copyright © 2018年 weixm. All rights reserved.
//

#include "CacheAndHolder.hpp"
CacheNode:: CacheNode(){
    this->key = 0;
    this->value = "";
    this->next = NULL;
    this->last = NULL;
};

//===============================
Cache:: Cache(){
    this->root = new CacheNode;
    this->tail = this->root;
    this->size = 0;
    this->limit = CacSize;
}

void Cache::put(int k, string v){
    if(this->size == 0){
        this->root->key = k;
        this->root->value = v;
        this->size = 1;
        this->tail = this->root;
    }else{
        CacheNode* tmp = new CacheNode;
        tmp->key = k;
        tmp->value = v;
        tmp->next = this->root;
        this->root->last = tmp;
        this->root = tmp;
        this->size++;
    }
    if(this->size > this->limit){
        CacheNode* tmp = this->tail;
        this->tail = this->tail->last;
        this->tail->next = NULL;
        
        delete tmp;
        this->size --;
    }
}

string Cache::search(int key){
    if(this->size == 0) return "";
    CacheNode* tmp = this->root;
    while(tmp->next != NULL){
        if(tmp->key == key) break;
        tmp = tmp->next;
    }
    if(tmp->key == key && tmp->last != NULL){
        tmp->last->next = tmp->next;
        this->root->last = tmp;
        tmp->next = this->root;
        this->root = tmp;
        string val = tmp->value;
        return val;
    }else if(tmp->key == key && tmp->last == NULL){
        string val = tmp->value;
        return val;
    }else{
        return "";
    }
}

void Cache::remove(int key){
    CacheNode* tmp = this->root;
    while(tmp->next != NULL){
        if(tmp->key == key) break;
        tmp = tmp->next;
    }
    if(tmp->key == key ){
        if(      tmp->last != NULL && tmp->next != NULL){
            tmp->last->next = tmp->next;
            this->size --;
            delete tmp;
        }else if(tmp->last == NULL && tmp->next != NULL){
            this->root = tmp ->next;
            this->root->last = NULL;
            this->size --;
            delete tmp;
        }else if(tmp->last != NULL && tmp->next == NULL){
            tmp->last->next = NULL;
            this->size--;
            delete tmp;
        }else{
            delete tmp;
            this->tail = this->root = new CacheNode();
            this->size = 0;
        }
    }else{
    }
}

void Cache::clear(){
    CacheNode* tmp = this->root;
    while(tmp->next != NULL){
        tmp = tmp->next;
        delete tmp->last;
    }
    tmp->last = NULL;
    this->root = tmp;
    this->size = 0;
}
//===============================
void Holder:: put(Pair rmd){
    this->posHolder.push(rmd);
}

Pair Holder:: pop(){
    Pair a = this->posHolder.front();
    this->posHolder.pop();
    return a;
}

bool Holder::empty(){
    return this->posHolder.empty();
}
//===============================
