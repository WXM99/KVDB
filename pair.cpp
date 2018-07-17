#include "pair.hpp"
Pair:: Pair(){
    total++;
    pos = total;
    id = "";
    contains = "";
}

Pair:: Pair(int pos){
    this->pos = pos;
    id = "";
    contains = ""; 
}
