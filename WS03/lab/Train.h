/* ------------------------------------------------------
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
Date    Thu Feb 3 2022

Workshop 3 part 1
Module: Train
Desc:   Module for Train object and functions
Filename: Train.h
-----------------------------------------------------------*/

#ifndef SDDS_TRAIN_H
#define SDDS_TRAIN_H 

namespace sdds {

    const int MAX_NAME_LEN =20;
    const int MAX_PEOPLE = 1000;
    const int MAX_SPEED = 320;

    const int SAFE_EMPTY_NUM_PEOPLE = -1;   // default value for number of people in safe empty state
    const int SAFE_EMPTY_SPEED = -1;        // default value for speed in safe empty state
    const int DISPLAY_SPEED_PRECISION = 2;  // how many decimals to display the speed at

    class Train {
        char name[MAX_NAME_LEN+1];
        int numPeople;
        double speed;

        // set object to safe empty state using invalid values
        // name is empty string, number of people and speed is -1
        void setSafeEmptyState();

    public:

        // initialize a Train object
        // receives the name of the train, the number of people on the train and the speed of the train
        // validates the data values received and uses these data values to set the respective data members, only if all of them are valid
        void set(const char*, int, double);

        // returns number of people on train
        int getNumberOfPeople() const;

        // returns name of train
        const char* getName() const;

        // returns speed of train
        double getSpeed() const;

        // returns true if object is in a safe empty state; false otherwise
        bool isSafeEmpty() const;

        // prints formatted object info to standard output
        // if object is in safe empty state print "Safe Empty State!" message instead
        void display() const;
    };
}

#endif // ! SDDS_TRAIN_H