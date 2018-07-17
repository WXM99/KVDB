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
    this->root = new Node;
    //char name_[100];
    //for(int i = 0 ; i < 100; i++){
    //    if(i < this->filename.size()) name_[i] = this->filename[i];
    //   else name_[i] = '\0';
    //}
    //this->file = fopen(name_, "rb+");
    fread(&this->scope, sizeof(int), 1, this->file);
    fread(&this->rID, sizeof(int), 1, this->file);
    this->readNode(this->root, this->rID);
}

void Tree:: splitNode(Node *p, Node *c, int i){
    
    Node* b = new Node;
    b->isleaf = c->isleaf;
    b->num = M;
    b->id = this->scope + 1;
    b->bro = c->bro;
    for(int j = 0; j < M; j++){
        b->keys[j] = c->keys[j+M];
        b->sons[j] = c->sons[j+M];
    }
    
    this->scope ++;
    c->num = M;
    c->bro = b->id;
    
    for(int j = p->num -1; j>i; j--){
        p->keys[j+1] = p->keys[j];
        p->sons[j+1] = p->sons[j];
    }
    
    p->keys[i+1] = b->keys[0];
    p->sons[i+1] = b->id;
    p->num++;
    
    this->writeNode(p);
    this->writeNode(c);
    this->writeNode(b);
    delete b;
    
}

void Tree:: insertNode_NF(Node *s, int k, unsigned int id){
    int i = s->num-1;
    if(s->isleaf){
        while(i >=0 && s->keys[i]>k){
            s->keys[i+1] = s->keys[i];
            s->sons[i+1] = s->sons[i];
            i--;
        }
        
        s->keys[i+1] = k;
        s->sons[i+1] = id;
        s->num ++;
        this->writeNode(s);
    }else{
        Node* tmp = new Node;
        while(i>=0 && s->keys[i]>k){
            i--;
        }
        
        if(i<0){
            i++;
            s->keys[i] = k;
        }
        this->writeNode(s);
        this->readNode(tmp, s->sons[i]);
        
        if(tmp->num == 2*M){
            splitNode(s, tmp, i);
            if(k > s->keys[i+1])
                i++;
            this->readNode(tmp, s->sons[i]);
        }
        insertNode_NF(tmp, k, id);
        delete tmp;
    }
}

int Tree:: search(int k){
    if(k < this->root->keys[0]) return -1;
    
    Node* root_cpy = this->root;
    Node* tmp = new Node;
    int i;
    while(true){
        i = root_cpy->num-1;
        while(i > 0 && root_cpy->keys[i] > k){
            i--;
        }
        if(root_cpy->isleaf) break;
        this->readNode(tmp, root_cpy->sons[i]);
        root_cpy = tmp;
    }
    if(root_cpy->keys[i] < k) return -1;
    
    int res = root_cpy->sons[i];
    delete tmp;
    tmp = NULL;
    return res;
}

void Tree:: insertKey(int k, int id){
    if(this->search(k)>0){
        cout << k << " has been in Tree." <<endl;
    }else{
        Node* rt = this->root;
        if(this->root->num == 2*M){
            Node* s = new Node;
            s->isleaf = false;
            s->num = 1;
            s->keys[0] = rt->keys[0];
            s->sons[0] = rt->id;
            s->id = this->scope + 1;
            s->bro = -1;
            this->writeNode(s);
            this->scope ++;
            this->writeNode(rt);
            this->splitNode(s, rt, 0);
            *this->root = *s;
            this->rID = s->id;
            insertNode_NF(s, k, id);
            delete s;
        }else{
            insertNode_NF(rt, k, id);
        }
    }
}

void Tree:: replaceKey(int oldkey, int newkey){
    Node* rt = this->root;
    Node* tmp = new Node;
    while(true){
        int i = rt->num - 1;
        while( i >= 0 && rt->keys[i] > oldkey)
            i --;
        if(rt->keys[i] == oldkey){
            rt->keys[i] = newkey;
            this->writeNode(rt);
        }
        if(rt->isleaf)
            break;
        this->readNode(tmp, rt->sons[i]);
        rt = tmp;

    }
    delete tmp;
}
