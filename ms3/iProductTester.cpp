/* ------------------------------------------------------
Final project Milestone 3
Module: iProductTester.cpp
Filename: main.cpp
Version 1.1
Author: Fardad Soleimanloo   2022-03-03
Revision History
-----------------------------------------------------------
Date          Reason
Mar 23        97: delete[] was wrong changed to delete
-----------------------------------------------------------*/
#include <iostream>
#include <fstream>
using namespace std;
#include "iProduct.h"
using namespace sdds;
class Product : public iProduct {
   char* dyntest{};
public:
   int readSku(std::istream& istr) {
      cout << "readSku" << endl;
      return 0;
   }
   int operator-=(int qty) {
      cout << "operator-=" << endl;
      return 0;
   }
   int operator+=(int qty) {
      cout << "operator+=" << endl;
      return 0;
   }
   operator double()const {
      cout << "operator double" << endl;
      return 0.;
   }
   operator bool()const {
      cout << "operator bool" << endl;
      return false;
   }
   int qtyNeeded()const {
      cout << "qtyNeeded" << endl;
      return 0;
   }
   int qty()const {
      cout << "qty" << endl;
      return 0;
   }
   void linear(bool isLinear) {
      cout << "Linear" << endl;
   }
   std::ofstream& save(std::ofstream& ofstr)const {
      cout << "save" << endl;
      return ofstr;
   }
   std::ifstream& load(std::ifstream& ifstr) {
      cout << "load" << endl;
      return ifstr;
   }
   std::ostream& display(std::ostream& ostr)const {
      operator bool();
      operator double();
      qtyNeeded();
      qty();
      operator==("");
      operator== (2);
      return ostr;
   }
   std::istream& read(std::istream& istr) {
      operator+=(1);
      operator-=(1);
      readSku(istr);
      linear(true);
      dyntest = new char[2345];
      return istr;
   }
   bool operator==(int sku)const {
      cout << "operator==" << endl;
      return false;
   }
   bool operator==(const char* desc)const {
      cout << "operator==(cosnt char*)" << endl;
      return false;
   }
   ~Product() {
      delete[] dyntest;
   }
};

int main() {
   iProduct* P = new Product;
   ifstream in("tst.txt");
   ofstream out("tst.txt");
   P->load(in);
   P->save(out);
   cout << *P;
   cin >> *P;
   delete P;
   return 0;
}