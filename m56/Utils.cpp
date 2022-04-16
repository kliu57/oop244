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
        int sourceSize = 0;
        int newDestSize = 0;

        delete [] destination;   // release destination memory storage if any
        destination = nullptr;

        if (source != nullptr) {
            sourceSize = static_cast<int>(strlen(source));

            // only proceed to copy if source has content
            // no need to check if source and dest memory addr are the same, since we deallocated dest
            // if they were the same address, after dealloc sourceSize is 0
            if (sourceSize) {
                newDestSize = sourceSize + 1;
                destination = new (nothrow) char[newDestSize];  // allocate new memory storage

                if (destination != nullptr) {
                    strcpy(destination, source);	// copy data to newly allocated memory location
                }
                else {
                    cout << "Unexpected error in alocpy" << endl;
                }
            }
        }
    }

    void Utils::aloConcat(char*& destination, const char* source) {
        char* newDest = nullptr;
        int destSize = 0;
        int newDestSize = 0;
        int sourceSize = 0;

        if (destination != nullptr) {
            destSize = static_cast<int>(strlen(destination));

            if (destSize) {
                if (source != nullptr) {
                    sourceSize = static_cast<int>(strlen(source));

                    // only proceed if source has content
                    if (sourceSize) {
                        newDestSize = destSize + sourceSize + 1;
                        newDest = new (nothrow) char[newDestSize];  // allocate new memory storage
                        if (newDest != nullptr) {
                            strcpy(newDest, destination);	// copy data to newly allocated memory location
                            strcat(newDest, source);        // concatenate
                            newDest[newDestSize-1] = '\0';

                            delete [] destination;
                            destination = newDest;  // set destination to point to new mem location
                        } else {
                            cout << "Unexpected error" << endl;
                        }
                    }
                }
            } else {
                // destination is empty string so just directly copy
                ut.alocpy(destination, source);
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

    int Utils::getintOrEnter(int min, int max, const char* prompt, const char* errMes, istream& istr) {
        int input = -1;
        char ch = 0;
        bool validInput = false;

        if (prompt != nullptr) {
            cout << prompt;  // display prompt
        }

        // check if user pressed enter
        ch = istr.peek();

        if (ch != '\n') {
            istr >> input;    // read from user input, input stream object will be set to fail state if user input is not an integer
            if (!istr.fail()) {
                if (input >= min && input <= max) {
                    validInput = true;
                }
            }
            
            // clear buffer
            istr.clear();
            istr.ignore(1000, '\n');

            while (!validInput) {     // prompt user again until valid input

                if (errMes != nullptr) {
                    cout << errMes;
                } else {
                    cout << "Value out of range [" << min << "<=val<=" << max << "], or press <ENTER>: ";  // user did not provide an error message so print the default one
                }

                ch = istr.peek();

                if (ch != '\n') {
                    istr >> input;    // read from user input, input stream object will be set to fail state if user input is not an integer
                    if (!istr.fail()) {
                        if (input >= min && input <= max) {
                            validInput = true;
                        }
                    }

                    // clear buffer
                    istr.clear();
                    istr.ignore(1000, '\n');
                } else {
                    istr.clear();
                    istr.ignore();
                    validInput = true;
                    input = -1;
                }
            }
        } else {
            istr.clear();
            istr.ignore();
            validInput = true;
            input = -1;
        }

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

    void Utils::getFileCstring(char*& dest, ifstream& ifstr, char delim) {
        const int maxSize = 200;        // this is how many characters we will attempt to read from the file before stopping
                                        // if delimiter is not reached, we will dynamically allocate memory and read further
        char fixedSizeString[maxSize];
        char ch = 0;
        int i = 0;
        bool hitDelim = false;

        ifstr.get(ch); 
        if (ch == delim) {
            hitDelim = true;
        }

        // read char by char until hitting delim or maxSize
        for (i = 0; i < maxSize-1 && !ifstr.eof() && !hitDelim; i++) {
            fixedSizeString[i] = ch;

            // read the cString stopping at the size limit
            if (i < maxSize-2) {
                ifstr.get(ch); 

                if (ch == delim) {
                    hitDelim = true;
                }
            }
        }   
        fixedSizeString[i] = '\0'; // make sure the cString is null terminated

        ut.alocpy(dest, fixedSizeString);    // set string as final

        // continue reading if still havent hit delimiter
        while (!hitDelim && !ifstr.eof()) {

            hitDelim = false;
            ifstr.get(ch); 
            if (ch == delim) {
                hitDelim = true;
            }
            // read char by char until hitting delim or maxSize
            for (i = 0; i < maxSize-1 && !ifstr.eof() && !hitDelim; i++) {
                fixedSizeString[i] = ch;

                // read the cString stopping at the size limit
                if (i < maxSize-2) {
                    ifstr.get(ch); 

                    if (ch == delim) {
                        hitDelim = true;
                    }
                }
            }   
            fixedSizeString[i] = '\0'; // make sure the fixedSizeString is null terminated
            
            aloConcat(dest, fixedSizeString);    // concat and set as final
        }

        // if reached the end and delimiter not found, set stream to fail state
        if (!hitDelim) {
            ifstr.setstate(ios::failbit);
        }
    }


    void Utils::formatCstring(char*& cstring) {
        int i = 0;
        int consecutiveSpaces = 0;
        int formattedSize = 0;
        int cstringSize = 0;
        char ch = 0;
        char* formatted = nullptr;
        int formattedIndex = 0;

        if (cstring != nullptr) {
            cstringSize = static_cast<int>(strlen(cstring));

            if (cstringSize) {
                formattedSize = cstringSize + 1;
                formatted = new (nothrow) char[formattedSize];  // dynamically make a copy of the cstring to store the formatted version

                if (formatted != nullptr) {
                    // skip leading whitespace
                    for (i = 0; i < cstringSize && isspace(cstring[i]); i++) {
                    }
                    // now i is the index of the first nonspace character

                    // go through the rest of the characters and add them to formatted, changing tabs and newlines to spaces
                    for (i = i; i < cstringSize; i++) {
                        ch = cstring[i];

                        if (isspace(ch)) {
                            formatted[formattedIndex++] = ' ';
                            consecutiveSpaces++;
                        } else {
                            formatted[formattedIndex++] = ch;
                            consecutiveSpaces = 0;
                        }
                    }

                    if (formattedIndex > 0) {
                        // if there are consectutive spaces at the end, remove them
                        if (consecutiveSpaces) {
                            formatted[formattedSize - consecutiveSpaces] = '\0';
                        } else {
                            formatted[i] = '\0';
                        }

                        // safely copy string
                        ut.alocpy(cstring, formatted);
                    }
                }
            }
        }

        if (!formattedIndex) {
            // formatted string is empty so set cstring to nullptr
            delete [] cstring;
            cstring = nullptr;
        }

        delete [] formatted;    // dealloc temp memory
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

    void Utils::getcstring(char*& dest, const char* prompt, const char* errMes, istream& istr) {
        string inputString;

        if (prompt != nullptr) {
            cout << prompt;  // display prompt
        }

        getline(istr, inputString); // get user input from console

        while (istr.fail() || !inputString.length()) {  // prompt user again if valid cstring was not read

            if (errMes != nullptr) {
                cout << errMes << ", retry: ";
            } else {
                cout << "Invalid entry, retry: ";  // user did not provide an error message so print the default one
            }

            getline(istr, inputString); // get user input from console
        }

        ut.alocpy(dest, inputString.c_str());
    }
}