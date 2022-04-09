/* ------------------------------------------------------
Final Project Milestone 5
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

    //void Utils::alocpy(char*& destination, const char* source) {
    //    delete [] destination;   // release destination memory storage if any
    //    destination = nullptr;
    //    if (source != nullptr) {
    //        destination = new (nothrow) char[static_cast<int>(strlen(source)+1)];  // allocate new memory storage
    //        if (destination != nullptr) {
    //            strcpy(destination, source);	// copy data to newly allocated memory location
    //        } else {
    //            cout << "Unexpected error in alocpy" << endl;
    //        }
    //    }
    //}



    void Utils::aloConcat(char*& destination, const char* source) {
        int newSize = 0;
        char* newDest = nullptr;

        if (destination != nullptr) {
            newSize = static_cast<int>(strlen(destination) + strlen(source) + 1);
            newDest = new (nothrow) char[newSize];  // allocate new memory storage
            if (newDest != nullptr) {
                strcpy(newDest, destination);	// copy data to newly allocated memory location
                strcat(newDest, source);        // concatenate
                newDest[newSize-1] = '\0';
                ut.alocpy(destination, newDest);    // copy concatenated data to destination
            } else {
                cout << "Unexpected error" << endl;
            }
            delete [] newDest;  // dealloc temp memory
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

    bool Utils::findInCstring(const char* cstring, const char* toFind) {
        bool found = false;
        const char* chPtr = strstr(cstring, toFind);
        if (chPtr != nullptr) {
            found = true;
        }
        return found;
    }

    //void Utils::getFileCstring(char*& dest, ifstream& ifstr, char delim) {
    //    const int maxSize = 200;        // this is how many characters we will attempt to read from the file before stopping
    //                                    // if delimiter is not reached, we will dynamically allocate memory and read further
    //    char fixedSizeString[maxSize];
    //    char ch=0;
    //    int i=0;
    //    bool hitDelim = false;

    //    ifstr.get(ch); 
    //    if (ch == delim) {
    //        hitDelim = true;
    //    }

    //    // read char by char until hitting delim or maxSize
    //    for (i = 0; i < maxSize-1 && !ifstr.eof() && !hitDelim; i++) {
    //        fixedSizeString[i] = ch;

    //        // read the cString stopping at the size limit
    //        if (i < maxSize-2) {
    //            ifstr.get(ch); 

    //            if (ch == delim) {
    //                hitDelim = true;
    //            }
    //        }
    //    }   
    //    fixedSizeString[i] = '\0'; // make sure the cString is null terminated

    //    ut.alocpy(dest, fixedSizeString);    // set string as final

    //    // continue reading if still havent hit delimiter
    //    while (!hitDelim && !ifstr.eof()) {

    //        hitDelim = false;
    //        ifstr.get(ch); 
    //        if (ch == delim) {
    //            hitDelim = true;
    //        }
    //        // read char by char until hitting delim or maxSize
    //        for (i = 0; i < maxSize-1 && !ifstr.eof() && !hitDelim; i++) {
    //            fixedSizeString[i] = ch;

    //            // read the cString stopping at the size limit
    //            if (i < maxSize-2) {
    //                ifstr.get(ch); 

    //                if (ch == delim) {
    //                    hitDelim = true;
    //                }
    //            }
    //        }   
    //        fixedSizeString[i] = '\0'; // make sure the fixedSizeString is null terminated
    //        
    //        aloConcat(dest, fixedSizeString);    // concat and set as final
    //    }

    //    // if reached the end and delimiter not found, set stream to fail state
    //    if (!hitDelim) {
    //        ifstr.setstate(ios::failbit);
    //    }
    //}

    void Utils::getFileCstring(char*& dest, ifstream& ifstr, char delim) {
        char temp[1000];
        ifstr.getline(temp, 1000, delim);    //this already throws away the delim
        ut.alocpy(dest, temp);
    }

    void Utils::formatCstring(char*& cstring) {
        int i = 0;
        int consecutiveSpaces = 0;
        int size = static_cast<int>(strlen(cstring) + 1);
        char ch = 0;
        char* formatted = new (nothrow) char[size];  // dynamically make a copy of the cstring to store the formatted version
        int formattedIndex = 0;

        if (formatted != nullptr) {

            formatted[0] = '\0';

            // skip leading whitespace
            for (i = 0; i < size-1 && isspace(cstring[i]); i++) {
            }
            // now i is the index of the first nonspace character

            // go through the rest of the characters and add them to formatted, changing tabs and newlines to spaces
            for (i = i; i < size-1; i++) {
                ch = cstring[i];

                if (isspace(ch)) {
                    formatted[formattedIndex++] = ' ';
                    consecutiveSpaces++;
                } else {
                    formatted[formattedIndex++] = ch;
                    consecutiveSpaces = 0;
                }
            }

            // if there are consectutive spaces at the end, remove them
            if (consecutiveSpaces) {
                formatted[size - consecutiveSpaces - 1] = '\0';
            } else {
                formatted[i] = '\0';
            }

            if (static_cast<int>(strlen(formatted))) {
                // safely copy string
                ut.alocpy(cstring, formatted);
            } else {
                // formatted string is empty so dealloc and set string to nullptr
                delete [] cstring;
                cstring = nullptr;
            }
        }

        delete [] formatted;    // dont need this anymore
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