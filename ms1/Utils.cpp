#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <ctime>
#include "Utils.h"
using namespace std;
namespace sdds {
   Utils ut;
   void Utils::testMode(bool testmode) {
      m_testMode = testmode;
   }
   void Utils::getSystemDate(int* year, int* mon, int* day) {
      if (m_testMode) {
         if(day) *day = sdds_testDay;
         if(mon) *mon = sdds_testMon;
         if(year) *year = sdds_testYear;
      }
      else {
         time_t t = std::time(NULL);
         tm lt = *localtime(&t);
         if (day) *day = lt.tm_mday;
         if (mon) *mon = lt.tm_mon + 1;
         if (year) *year = lt.tm_year + 1900;
      }
   }
   int Utils::daysOfMon(int month, int year)const {
      int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
      int mon = (month >= 1 && month <= 12 ? month : 13)-1;
      return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
   }
   
   void Utils::alocpy(char*& destination, const char* source) {
       delete [] destination;   // release destination memory storage if any
       destination = nullptr;
       if (source != nullptr) {
           destination = new (nothrow) char[strlen(source)+1];  // allocate new memory storage
           if (destination != nullptr) {
               strcpy(destination, source);	// copy data to newly allocated memory location
           }
       }
   }

   int Utils::getint(const char* prompt) {
       int input = 0;
       if (prompt != nullptr) {
           cout << prompt;  // display prompt
       }
       cin >> input;    // read from user input, input stream object will be set to fail state if user input is not an integer
       while (cin.fail()) {     // prompt user again until input stream object is not in fail state
           cout << "Invalid Integer, retry: ";
           cin.clear();
           cin.ignore(1000, '\n');  // clear buffer
           cin >> input;    // read from user input, input stream object will be set to fail state if user input is not an integer
       }
       return input;
   }

   int Utils::getint(int min, int max, const char* prompt, const char* errMes) {
       int input = 0;
       bool inRange = false;
       if (prompt != nullptr) {
           cout << prompt;  // display prompt
       }
       cin >> input;    // read from user input, input stream object will be set to fail state if user input is not an integer
       if (!cin.fail()) {
           if (input >= min && input <= max) {
               inRange = true;
           }
       }
       while (cin.fail() || !inRange) {     // prompt user again until input stream object is not in fail state
           if (errMes != nullptr) {
               cout << errMes << ", retry: ";   // display argument error message
           } else {
               cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
           }
           cin.clear();
           cin.ignore(1000, '\n');  // clear buffer
           cin >> input;    // read from user input, input stream object will be set to fail state if user input is not an integer
           if (!cin.fail()) {
               if (input >= min && input <= max) {
                   inRange = true;
               }
           }
       }
       return input;
   }
}