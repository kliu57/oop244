/* ------------------------------------------------------
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
Date    Thu Jan 27 2020

Workshop 2 part 1
Module: Car
Desc:   Module that hold information for passing car
Filename: Car.h
-----------------------------------------------------------*/

#ifndef SDDS_CAR_H
#define SDDS_CAR_H 

namespace sdds {

    const int MAX_MAKE_AND_MODEL_LEN = 60;
    const int MAX_PLATE_LEN = 8;

    struct Car {
        char plate[MAX_PLATE_LEN+1];

        char* makeAndModel = nullptr;
        
        int time;
    };

    // prints program start message
    void VBPLE_Title();

    // initialize variables and dynamically allocates memory
    void initialize(int allocSize);

    // deletes allocated memory pointed by the make and model pointer in the Car structure, then set it to nullptr
    void deallocate(Car& C);

    // overloads the read function
    // Read the information of a car passing the border in a comma-separated format from the console and dynamically
    // hold the make an model in the make and model pointer of the Car structure
    // Return true if a Car is read from the console or return false if "X," is entered instead.
    bool read(Car& C);

    // formats and prints car object
    void print(const Car& C);

    // records the passage of a car by adding its information to the Car Array 
    void record(const Car& C);

    // function called at the end of the program
    // go through all the elements of the car array pointed by The Car Pointer and prints them
    // deallocate dynamic memory
    void endOfDay();
}

#endif // ! SDDS_CSTRTOOLS_H