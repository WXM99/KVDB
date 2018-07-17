#include "database.hpp"
#include <iostream>

using namespace std;
int Pair:: total  = 0;

int main(){
    DB mydb = DB();
    char op = 'O';
    while(op != 'Q'){
        cout << "'C' for creat;"<<endl;
        cout << "'I' for insert;"<<endl;
        cout << "'S' for search;"<<endl;
        cout << "'R' for remove;"<<endl;
        cout << "'G' for save;"<<endl;
        cout << "'Q' for quit;"<<endl;
        cout << "Ender oprator: ";
        cin >> op;
        switch (op) {
            case 'C':
                mydb.creat();
                break;
            case 'I':
                mydb.insert();
                break;
            case 'S':
                mydb.search();
                break;
            case 'R':
                mydb.remove();
                break;
            case 'G':
                mydb.close();
                break;
            case 'Q':
                cout << "Bye!" <<endl;
                break;
            default:
                cout << "Invalid operator." << endl;
                break;
        }
    }
}
