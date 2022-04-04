/* ------------------------------------------------------
Final Project Milestone 3
Module: Utils
Filename: Utils.cpp
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <string>
#include <ctime>
#include <iomanip>
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
            time_t t = time(NULL);
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
            } else {
                cout << "Unexpected error in alocpy" << endl;
            }
        }
    }

    int Utils::getint(const char* prompt, istream& istr) {
        int input = 0;
        if (prompt != nullptr) {
            cout << prompt;  // display prompt
        }
        istr >> input;    // read from user input, input stream object will be set to fail state if user input is not an integer
        while (istr.fail()) {     // prompt user again until input stream object is not in fail state
            cout << "Invalid Integer, retry: ";
            istr.clear();
            istr.ignore(1000, '\n');  // clear buffer
            istr >> input;    // read from user input, input stream object will be set to fail state if user input is not an integer
        }
        return input;
    }

    int Utils::getint(int min, int max, const char* prompt, const char* errMes, istream& istr) {
        int input = 0;
        bool inRange = false;
        if (prompt != nullptr) {
            cout << prompt;  // display prompt
        }
        istr >> input;    // read from user input, input stream object will be set to fail state if user input is not an integer
        if (!istr.fail()) {
            if (input >= min && input <= max) {
                inRange = true;
            }
        }
        while (istr.fail() || !inRange) {     // prompt user again until input stream object is not in fail state
                                              // display error message according to the situation
            if (istr.fail()) {
                if (errMes != nullptr) {
                    cout << errMes << ", retry: ";
                } else {
                    cout << "Value out of range [" << min << "<=val<=" << max << "]: ";  // user did not provide an error message so print the default one
                }
            } else {
                // assume !inRange
                cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
            }

            istr.clear();
            istr.ignore(1000, '\n');  // clear buffer
            istr >> input;    // read from user input, input stream object will be set to fail state if user input is not an integer
            if (!istr.fail()) {
                if (input >= min && input <= max) {
                    inRange = true;
                }
            }
        }

        // clear buffer
        istr.clear();
        istr.ignore(1000, '\n');

        return input;
    }

    double Utils::getdouble(double min, double max, const char* prompt, const char* errMes, istream& istr) {
        double input = 0.0;
        bool inRange = false;

        // set precision
        cout.setf(ios::fixed);
        cout.precision(2);

        if (prompt != nullptr) {
            cout << prompt;  // display prompt
        }
        istr >> input;    // read from user input, input stream object will be set to fail state if user input is not an integer
        if (!istr.fail()) {
            if (input >= min && input <= max) {
                inRange = true;
            }
        }
        while (istr.fail() || !inRange) {     // prompt user again until input stream object is not in fail state
                                              // display error message according to the situation
            if (istr.fail()) {
                if (errMes != nullptr) {
                    cout << errMes << ", retry: ";
                } else {
                    cout << "Value out of range [" << min << "<=val<=" << max << "]: ";  // user did not provide an error message so print the default one
                }
            } else {
                // assume !inRange
                cout << "Value out of range [" << min << "<=val<=" << max << "]: ";
            }

            istr.clear();
            istr.ignore(1000, '\n');  // clear buffer
            istr >> input;    // read from user input, input stream object will be set to fail state if user input is not an integer
            if (!istr.fail()) {
                if (input >= min && input <= max) {
                    inRange = true;
                }
            }
        }

        // clear buffer
        istr.clear();
        istr.ignore(1000, '\n');

        // set precision back
        cout.unsetf(ios::fixed);
        cout.precision(6);

        return input;
    }

    int Utils::getFileLength(ifstream & ifstr) {
        int len = 0;
        if (ifstr) {
            streampos cur = ifstr.tellg();  // save current read position
            ifstr.seekg(0, ios::end);   // go to end
            len = (int)ifstr.tellg();   // get difference in positions
            ifstr.seekg(cur);   // return to the saved read position
        }
        return len;
    }

    bool Utils::findInCstring(const char* cstring, const char* toFind) {
        bool found = false;
        const char* chPtr = strstr(cstring, toFind);
        if (chPtr != nullptr) {
            found = true;
        }
        return found;
    }

    void Utils::getcstring(char*& dest, ifstream& ifstr, char delim) {
        int fileSize = 0;
        char* tempCstring = nullptr;

        delete [] dest;     // dealloc old memory
        dest = nullptr;

        fileSize = ut.getFileLength(ifstr);           // get length of stream

        if (fileSize) {
            tempCstring = new (nothrow) char[fileSize+1];	// allocate temp memory storage

            if (tempCstring != nullptr) {
                ifstr.get(tempCstring, (fileSize+1), delim);

                dest = new (nothrow) char[fileSize+1];	// allocate new memory storage

                if (dest != nullptr) {
                    strcpy(dest, tempCstring);      // copy string to new memory location
                } else {
                    cout << "Unexpected error in getcstring Code#B" << endl;
                }

            } else {
                cout << "Unexpected error in getcstring Code#A" << endl;
            }

            delete [] tempCstring;  // dealloc temp memory storage
        }
    }

    void Utils::getcstring(char*& dest, istream& istr) {
        string inputString;

        getline(istr, inputString); // get user input from console

        if (inputString.length()) {
            ut.alocpy(dest, inputString.c_str());
        } else {
            delete [] dest;
            dest = nullptr;
        }
    }
}