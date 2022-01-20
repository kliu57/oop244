#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>
using namespace std;

namespace liu
{
    int show(const char s){

        int repeatNum = 12;

        for (auto i = 0; i < repeatNum; i++) {
            cout << s;
        }

        cout << endl;

        return repeatNum;
    }
}

int main(){

    const char myChar = '#';

    cout << "WELCOME TO OOP244!!!\n";
    cout << liu::show(myChar);
    cout << "\nSEE YOU!";
    cout << endl;

    return 0;
}