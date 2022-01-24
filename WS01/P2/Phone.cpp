/* ------------------------------------------------------
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
Date    Sun Jan 23 2020

Workshop 1 part 2
Module: Phone
Desc:   
Filename: Phone.cpp
-----------------------------------------------------------*/


#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <iomanip>
using namespace std;

#include "Phone.h"
#include "cStrTools.h"

namespace sdds {


    void phoneDir(const char* programTitle, const char* fileName) {

        bool endProgram = false;

        FILE* fptr = nullptr;

        char name[MAX_NAME_LEN+1];
        char area[MAX_AREA_LEN+1];
        char prefix[MAX_PREFIX_LEN+1];
        char number[MAX_NUMBER_LEN+1];
        char partialName[MAX_NAME_LEN+1];
        char nameLower[MAX_NAME_LEN+1];

        cout << programTitle << " phone direcotry search" << endl; 
        cout << "-------------------------------------------------------" << endl;

        fptr = fopen(fileName , "r");

        if (fptr != nullptr) {

            cout << "Enter a partial name to search (no spaces) or enter '!' to exit" << endl;

            cout << "> ";

            cin >> partialName;     // get user input

            if (strLen(partialName) == 1 && partialName[0] == '!') {
                endProgram = true;
            }

            while (!endProgram) {   // loop until user chooses to quit the program

                toLowerCaseAndCopy(partialName, partialName);   // convert to lower case

                while (fscanf(fptr, "%[^\t]\t%s\t%s\t%s\n", name, area, prefix, number) != EOF) {

                    toLowerCaseAndCopy(nameLower, name);   // convert to lower case

                    if(strStr(nameLower, partialName) != nullptr) {     // check if partial name exists in name
                        cout << name << ": (" << area << ") " << prefix << "-" << number << endl;   // print record
                    }

                }

                rewind(fptr);   // rewind file so we read from the beginning again

                cout << "Enter a partial name to search (no spaces) or enter '!' to exit" << endl;

                cin >> partialName;

                if (strLen(partialName) == 1 && partialName[0] == '!') {
                    endProgram = true;
                }
            }

            fclose(fptr);
            fptr = nullptr;

        } else {
            cout << fileName << " file not found!" << endl; 
        }
        
        cout << "Thank you for using " << programTitle << " directory." << endl;
    }
}