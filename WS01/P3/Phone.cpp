/* ------------------------------------------------------
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
Date    Sun Jan 23 2020

Workshop 1 part 2
Module: Phone
Desc:   Module that reads phone directory file and returns records that contain user input
Filename: Phone.cpp
-----------------------------------------------------------*/


#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
using namespace std;

#include "Phone.h"
#include "cStrTools.h"

namespace sdds {

    void displayTitle(const char* programTitle) {
        cout << programTitle << " phone direcotry search" << endl; 
        cout << "-------------------------------------------------------" << endl;
    }

    void displayEndMessage(const char* programTitle) {
        cout << "Thank you for using " << programTitle << " directory." << endl;
    }

    int getNumLinesFile(std::FILE* fptr) {
        int numLines = 0;

        char* name = nullptr;
        char* area = nullptr;
        char* prefix = nullptr;
        char* number = nullptr;

        name = new char[MAX_NAME_LEN+1];    // allocate dynamic memory
        area = new char[MAX_AREA_LEN+1];
        prefix = new char[MAX_PREFIX_LEN+1];
        number = new char[MAX_NUMBER_LEN+1];

        while (fscanf(fptr, "%[^\t]\t%s\t%s\t%s\n", name, area, prefix, number) != EOF) {   // find num lines in file
            numLines++; 
        }

        rewind(fptr);   // rewind file so it is read from beginning

        delete [] name;     //deallocate dynamic memory
        delete [] area;
        delete [] prefix;
        delete [] number;
        name = nullptr;
        area = nullptr;
        prefix = nullptr;
        number = nullptr;

        return numLines;
    }

    void readFile(std::FILE* fptr, Phone* phonePtr, int phoneDirLen) {
        for (int i = 0; i < phoneDirLen && fscanf(fptr, "%[^\t]\t%s\t%s\t%s\n", phonePtr[i].name, phonePtr[i].area, phonePtr[i].prefix, phonePtr[i].number) != EOF; i++);   // save file info into struct array
    }

    void displayAllPartialMatch(char* partialName, char* nameLower, const Phone* phonePtr, int phoneDirLen) {

        toLowerCaseAndCopy(partialName, partialName);   // convert to lower case

        for (int i = 0; i < phoneDirLen; i++) {   // go through struct array

            toLowerCaseAndCopy(nameLower, phonePtr[i].name);   // convert to lower case

            if(strStr(nameLower, partialName) != nullptr) {     // check if partial name exists in name
                cout << phonePtr[i].name << ": (" << phonePtr[i].area << ") " << phonePtr[i].prefix << "-" << phonePtr[i].number << endl;   // print record
            }
        }
    }

    void phoneDir(const char* programTitle, const char* fileName) {

        bool endProgram = false;
        int numLinesFile = 0;
        FILE* fptr = nullptr;
        Phone* phonePtr = nullptr;
        char* partialName = nullptr;
        char* nameLower = nullptr;
        
        partialName = new char[MAX_NAME_LEN+1];
        nameLower = new char[MAX_NAME_LEN+1];

        displayTitle(programTitle);

        fptr = fopen(fileName , "r");   // open file for reading

        if (fptr != nullptr) {      // proceed if file was read successfully

            numLinesFile = getNumLinesFile(fptr);   // get number of records in file

            phonePtr = new Phone[numLinesFile];     // allocate dynamic memory

            readFile(fptr, phonePtr, numLinesFile); // populate array of Phone structs with file data

            fclose(fptr);       // close file for reading
            fptr = nullptr;


            cout << "Enter a partial name to search (no spaces) or enter '!' to exit" << endl << "> ";
            cin >> partialName;     // get user input

            if (strLen(partialName) == 1 && partialName[0] == '!') {    // check if user wants to quit program
                endProgram = true;
            }

            while (!endProgram) {   // loop until user chooses to quit the program

                displayAllPartialMatch(partialName, nameLower, phonePtr, numLinesFile);

                cout << "Enter a partial name to search (no spaces) or enter '!' to exit" << endl << "> ";
                cin >> partialName;     // get user input

                if (strLen(partialName) == 1 && partialName[0] == '!') {    // check if user wants to quit program
                    endProgram = true;
                }
            }

            delete [] phonePtr;     // deallocate dynamic memory
            phonePtr = nullptr;
        } else {
            cout << fileName << " file not found!" << endl;
        }
        
        delete [] partialName;  // deallocate dynamic memory
        delete [] nameLower;
        partialName = nullptr;
        nameLower = nullptr;

        displayEndMessage(programTitle);
    }
}