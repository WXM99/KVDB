//
//  bptree.cpp
//  Database
//
//  Created by  魏小渺 on 2018/7/16.
//  Copyright © 2018年  魏小渺. All rights reserved.
//

#include "bptree.hpp"
#include <fstream>
#include <sstream>
Node:: Node(){
    pos = 1;//differ from pos in datafile
    num = 0;
    isleaf = true;
    bro = -1;
}

Tree:: Tree(){
    root = new Node;
    scope = 1;
    rtPos = 1;
}

// scope and rtPos are stored in the beginning
// that's why "+2*(sizeof(int))"
void Tree:: writeNode(Node* node){
    fseek(this->file, sizeof(Node)*(node->pos -1) + 2*sizeof(int), SEEK_SET);
    fwrite(node, sizeof(Node), 1, this->file);
}

void Tree:: readNode(Node* node, int pos){
    fseek(this->file, (sizeof(Node))*(pos - 1) + 2*sizeof(int), SEEK_SET);
    fread(node, sizeof(Node), 1, this->file);
}


void Tree:: initIndex(string path){
    path =  path + ".idx";
    this->filename = path ;
    char name_[100];
    string_to_char(name_, path);
    Node* root_cpy = this->root;
    
    this->file = fopen(name_, "wb");
    fwrite(&this->scope, sizeof(int), 1, this->file);
    fwrite(&this->rtPos, sizeof(int), 1, this->file);
    this->writeNode(root_cpy);
    fclose(this->file);
    delete root_cpy;
    this->root = NULL;
    
    this->root = new Node;
    this->file = fopen(name_, "rb+");
    fread(&this->scope, sizeof(int), 1, this->file);
    fread(&this->rtPos, sizeof(int), 1, this->file);
    this->readNode(this->root, this->rtPos);
}


int Tree:: openIndex(string path){
    path =  path + ".idx";
    ifstream test;  // detect whether path exist
    test.open(path);
    if(test.good()){
        char name_[100];
        string_to_char(name_, path);
        
        this->file = fopen(name_, "rb+");
        this->root = new Node;
        fread(&this->scope, sizeof(int), 1, this->file);
        fread(&this->rtPos, sizeof(int), 1, this->file);
        this->readNode(this->root, this->rtPos);
        this->filename = name_;
        return 0;
    }else{
        return -1;
    }
}

void Tree:: closeIndex(){
    fclose(this->file);
    char name_[100];
    string_to_char(name_, this->filename);
    this->file = fopen(name_, "rb+");
    fwrite(&this->scope, sizeof(int), 1, this->file);
    fwrite(&this->rtPos, sizeof(int), 1, this->file);
}


/*=================================================*/
void Tree:: splitNode(Node *p, Node *c, int i){
    
    Node* b = new Node;
    b->isleaf = c->isleaf;
    b->num = M;
    b->pos = this->scope + 1;
    b->bro = c->bro;
    // push back
    for(int j = 0; j < M; j++){
        b->keys[j] = c->keys[j+M];
        b->sons[j] = c->sons[j+M];
    }
    
    this->scope ++;
    c->num = M;
    c->bro = b->pos;
    
    // push ahead
    for(int j = p->num -1; j>i; j--){
        p->keys[j+1] = p->keys[j];
        p->sons[j+1] = p->sons[j];
    }
    
    p->keys[i+1] = b->keys[0];
    p->sons[i+1] = b->pos;
    p->num++;
    
    this->writeNode(p);
    this->writeNode(c);
    this->writeNode(b);
    delete b;
    
}

void Tree:: insertNodeToNotFull(Node *s, int k, unsigned int pos){
    int i = s->num-1;
    if(s->isleaf){
        while(i >=0 && s->keys[i]>k){
            s->keys[i+1] = s->keys[i];
            s->sons[i+1] = s->sons[i];
            i--;
        }
        
        s->keys[i+1] = k;
        s->sons[i+1] = pos;
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
        insertNodeToNotFull(tmp, k, pos);
        delete tmp;
    }
}

int Tree:: searchPos(int k){
    
    if( this->root->num  == 0){
        return -1;
    }
    
    if(k < this->root->keys[0]) {return -1;}
    Node* move = this->root;
    Node* tmp = new Node;
    int i =  move->num-1;
    while(true){// count down
        i = move->num-1;
        while(i > 0 && move->keys[i] > k){
            i--;
        }
        if(move->isleaf) break;
        this->readNode(tmp, move->sons[i]);
        move = tmp;
    }
    if(move->keys[i] < k) return -1;
    
    int pos = move->sons[i]; // pos of data
    delete tmp;
    return pos;
}

void Tree:: insertKey(int k, int pos){
    Node* rt = this->root;
    if(this->root->num == 2*M){
        Node* s = new Node;
        s->isleaf = false;
        s->num = 1;
        s->keys[0] = rt->keys[0];
        s->sons[0] = rt->pos;
        s->pos = this->scope + 1;
        s->bro = -1;
        this->writeNode(s);
        this->scope ++;
        this->writeNode(rt);
        this->splitNode(s, rt, 0);
        *this->root = *s;
        this->rtPos = s->pos;
        insertNodeToNotFull(s, k, pos);
        delete s;
    }else{
        insertNodeToNotFull(rt, k, pos);
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

int Tree:: preDelete(Node* p, Node* x, unsigned int i){
    Node* tmp = new Node;
    Node* left = NULL;
    Node* right = NULL;
    if(i > 0){
        this->readNode(tmp, p->sons[i-1]);
        left = tmp;
        if(left->num > M){
            for(int j = x->num; j>0; j--){
                x->keys[j] = x->keys[j-1];
                x->sons[j] = x->sons[j-1];
            }
            x->num --;
            x->keys[0] = left->keys[left->num-1];
            x->sons[0] = left->sons[left->num-1];
            this->writeNode(x);
            left->num--;
            this->writeNode(left);
            p->keys[i] = x->keys[0];
            writeNode(p);
            return 0;
        }
    }
    
    if(i < p->num-1){
        readNode(tmp, p->sons[i+1]);
        right = tmp;
        if(right->num > M){
            x->keys[x->num] = right->keys[0];
            x->sons[x->num] = right->sons[0];
            x->num ++;
            this->writeNode(x);
            
            for(int j = 0; j < right->num-1; j++){
                right->keys[j] = right->keys[j+1];
                right->sons[j] = right->sons[j+1];
            }
            right->num --;
            this->writeNode(right);
            
            p->keys[i+1] = right->keys[0];
            this->writeNode(p);
            return 0;
        }
    }
    
    if(left == tmp){
        for(int j =0; j<M; j++){
            left->keys[M+j] = x->keys[j];
            left->sons[M+j] = x->sons[j];
        }
        left->num += M;
        left->bro = x->bro;
        this->writeNode(left);
        
        for(int j = i; j < p->num -1; j++){
            p->keys[j] = p->keys[j+1];
            p->sons[j] = p->sons[j+1];
        }
        p->num --;
        this->writeNode(p);
        *x = *left;
    }else{
        for(int j = 0; j < M; j++){
            x->keys[M+j] = right->keys[j];
            x->sons[M+j] = right->sons[j];
        }
        x->num += M;
        x->bro = right->bro;
    }
    delete tmp;
    left = right = tmp = NULL;
    return 0;
}

int Tree:: deleteKeyInNode(Node* p, int k){
    unsigned int i = p->num-1;
    if(i == -1 ) {
        return -1;
    }
    while(p->keys[i] > k){
        i --;
    }
    
    if(p->isleaf){
        for(int j = i; j < p->num-1; j++){
            p->keys[j] = p->keys[j+1];
            p->sons[j] = p->sons[j+1];
        }
        p->num--;
        this->writeNode(p);
        if(i == 0)
            this->replaceKey(k, p->keys[i]);
        return p->keys[i];
    }
    else{
        Node* x = new Node;
        this->readNode(x, p->sons[i]);
        if(x->num > M) return this->deleteKeyInNode(x, k);
        else{
            this->preDelete(p, x, i);
            return this->deleteKeyInNode(x, k);
        }
    }
    
}

void Tree:: deleteKey(int k){
    
    Node* rt = this->root;
    Node* tmp = new Node;
    int i =  rt->num-1;
    while(true){// count down
        i = rt->num-1;
        while(i > 0 && rt->keys[i] > k){
            i--;
        }
        if(rt->isleaf) break;
        this->readNode(tmp, rt->sons[i]);
        rt = tmp;
    }// now I got the node contains key which is rt
    
    this->deleteKeyInNode(rt, k);
    if(rt->num == 1){//degrade to a <rt-sons[0]> tree
        this->rtPos = rt->sons[0];
        this->readNode(this->root, rt->sons[0]);
        this->scope--;
    }
    delete tmp;
    
}


void Tree:: string_to_char(char* ch, string input){
    for(int i = 0; i < 100; i++){
        if(i < input.size()) ch[i] = input[i];
        else ch[i] = '\0';
    }
}
