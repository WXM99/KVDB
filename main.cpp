// this is the vision 9
#include <iostream>
#include "./DB/database.hpp"
#include <sstream>
using namespace std;
int Pair:: total  = 0;

void operations();

int main(){
    DB* mydb = new DB();
    cout << "--------------simple-databace----------------"<<endl;
    cout << "---Enter'O' for open existed project.--------"<<endl;
    cout << "---Enter'C' for creat an empty project.------"<<endl;
    cout << "---Enter'H' for operation help when opened---"<<endl;
    cout << "---Enter'B' for creating a big data----------"<<endl;
    cout << ">> ";
    string mode;
    cin >> mode; char coro = mode[0];
    while(true){
        if(coro == 'C' || coro == 'c'){
            mydb->IOcreate();
            break;
        }else if(coro == 'O' || coro == 'o'){
            mydb->IOopen();
            break;
        }else if(coro == 'B' || coro == 'b'){
            cout << "Input the name of DB: " << endl;
            string name;
            cin >> name;
            
            cout << "Input the scale of DB: " << endl;
            int scale;
            cin >> scale;
            
            cout << "Input each value of DB: " << endl;
            char value[100];
            cin >> value;
            
            cout << "building testDB......"<<endl;
            mydb->create(name);
            mydb->BigSize(scale,value);
            cout << "testDB has been built."<<endl;
            break;
        }else if(coro == 'H' || coro == 'h'){
            operations();
            cout << ">> ";
            cin  >> mode; coro = mode[0];
        }
        else{
            cout << "Invalid input, try again.\n>> ";
            cin  >> mode; coro = mode[0];
        }
    }
    
    char op = '-';
    while(op != 'Q' && op != 'q' ){
        cout << "Enter oprator: ";
        string input;
        cin >> input;
        op = input[0];
        switch (op) {
            case 'H':case 'h':
                operations();
                break;
            case 'I':case 'i':
                mydb->IOinsert();
                break;
            case 'S':case 's':
                mydb->IOget();
                break;
            case 'F':case 'f':
                mydb->IOrangeGet();
                break;
            case 'D':case 'd':
                mydb->IOremove();
                break;
            case 'R':case 'r':
                mydb->IOreplace();
                break;
            case 'Q':case 'q':
                mydb->save();
                cout << "Bye!" <<endl;
                break;
            case 'O':case 'o':
                mydb->IOcreate();
                break;
            default:
                cout << "Invalid operator." << endl;
                break;
        }
    }
    return 0;
}

void operations(){
    cout << "'I' for insert;"<<endl;
    cout << "'S' for search;"<<endl;
    cout << "'F' for find range;"<<endl;
    cout << "'D' for delete;"<<endl;
    cout << "'R' for replace;"<<endl;
    cout << "'Q' for quit and save;"<<endl;
}
