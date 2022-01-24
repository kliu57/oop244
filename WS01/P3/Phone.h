/* ------------------------------------------------------
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
Date    Sun Jan 23 2020

Workshop 1 part 2
Module: Phone
Desc:   Module that reads phone directory file and returns records that contain user input
Filename: Phone.h
-----------------------------------------------------------*/

#ifndef SDDS_PHONE_H
#define SDDS_PHONE_H 

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>

namespace sdds {

    const int MAX_NAME_LEN = 50;
    const int MAX_AREA_LEN = 3;
    const int MAX_PREFIX_LEN = 3;
    const int MAX_NUMBER_LEN = 4;

    struct Phone {
        char name[MAX_NAME_LEN+1];
        char area[MAX_AREA_LEN+1];
        char prefix[MAX_PREFIX_LEN+1];
        char number[MAX_NUMBER_LEN+1];
    };

    void displayTitle(const char* programTitle);

    void displayEndMessage(const char* programTitle);

    void readFile(std::FILE* fptr, Phone* phoneListPtr, int phoneListLen);

    int getNumLinesFile(std::FILE* fptr);

    void displayAllPartialMatch(char* partialName, char* nameLower, const Phone* phonePtr, int phoneDirLen);

    // runs the phone directory appication
    void phoneDir(const char* programTitle, const char* fileName);
}

#endif // ! SDDS_PHONE_H