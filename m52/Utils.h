/* ------------------------------------------------------
Final Project Milestone 5
Module: Utils
Filestatus: Utils.h
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H
#include <iostream>
#include <fstream>
namespace sdds {
    const int sdds_testYear = 2022;
    const int sdds_testMon = 03;
    const int sdds_testDay = 31;
    class Utils {
        bool m_testMode = false;
    public:
        void getSystemDate(int* year = nullptr, int* mon = nullptr, int* day = nullptr);
        int daysOfMon(int mon, int year)const;
        void testMode(bool testmode = true);

        // Safely allocates memory in destination and copies the source into it
        void alocpy(char*& destination, const char* source);

        // Safely allocates memory in destination and concatenates two cstrings
        void aloConcat(char*& destination, const char* source);

        // Continue to prompt the user to enter an integer until a valid one is read
        // Returns the read integer
        int getint(const char* prompt = nullptr, std::istream& istr = std::cin);

        // Continue to prompt the user to enter an integer until a valid one within the given range is read
        // Returns the read integer
        int getint(int min, int max, const char* prompt = nullptr, const char* errMes = nullptr, std::istream& istr = std::cin);

        // Continue to prompt the user to enter a double until a valid one within the given range is read
        // Returns the read double
        double getdouble(double min, double max, const char* prompt = nullptr, const char* errMes = nullptr, std::istream& istr = std::cin);

        // Returns true if a cstring exists in another cstring, false otherwise
        bool findInCstring(const char* cstring, const char* toFind);

        // Read a cstring from a file until delimiter reached
        void getFileCstring(char*& dest, std::ifstream& ifstr, char delim = '\n');

        // format cstring by trimming leading/trailing whitespace, and changing all tabs, \n, to ' '
        // if cstring has no nonspace characters, deallocate and set to nullptr
        void formatCstring(char*& cstring);

        // Read a cstring from console
        void getcstring(char*& dest, std::istream& istr = std::cin);
    };
    extern Utils ut;
}

#endif // !SDDS_UTILS_H
