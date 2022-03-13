/* ------------------------------------------------------
Final project Milestone 2
Module: Menu and AidMan
Filename: main.cpp
Version 1.0
Author: Fardad Soleimanloo   2022-03-03
Revision History
-----------------------------------------------------------
Date          Reason
-----------------------------------------------------------*/
#include <iostream>
#include "AidMan.h"
#include "Utils.h"
int main() {
   std::cout << "Enter the following:\nabc\n1\n2\n3\n4\n5\n6\n7\n8\n0\n--------\n";
   sdds::ut.testMode();
   sdds::AidMan().run();
   return 0;
}