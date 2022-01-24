/* ------------------------------------------------------
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
Date    Sun Jan 23 2020

Workshop 1 part 2
Module: Phone
Desc:   
Filename: Phone.h
-----------------------------------------------------------*/

#ifndef SDDS_PHONE_H
#define SDDS_PHONE_H 

namespace sdds {

    const int MAX_NAME_LEN = 50;
    const int MAX_AREA_LEN = 3;
    const int MAX_PREFIX_LEN = 3;
    const int MAX_NUMBER_LEN = 4;

    // runs the phone directory appication
    void phoneDir(const char* programTitle, const char* fileName);
}

#endif // ! SDDS_PHONE_H