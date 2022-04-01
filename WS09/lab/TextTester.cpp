/* ------------------------------------------------------
Workshop 8 part 1
Module: N/A
Filename: TextTester.cpp
Version 1
Author: Fardad Soleimanloo  22/03/26
Revision History
-----------------------------------------------------------
Date       Reason
22/03/29   added #include <fstream> by Ali Omar
-----------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include "HtmlText.h"
#include "Text.h"
using namespace std;
using namespace sdds;
void displayFile(const char* filename) {
   cout << "File: " << filename << endl;
   cout << "==================================================" << endl;
   ifstream fin(filename);
   char ch = 0;
   while (fin.get(ch)) {
      cout << ch;
   }
   cout << endl << "==================================================" << endl;
}
int main() {
   Text T;
   Text Y;
   ifstream test("test.txt");
   test >> T;
   Y = T;
   Text Z = Y;
   T = Z;
   cout << "*" << T << "*" << endl;
   return 0;
}
