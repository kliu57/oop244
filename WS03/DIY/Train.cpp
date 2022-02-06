/* ------------------------------------------------------
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
Date    Sun Feb 6 2022

Workshop 3 part 2
Module: Train
Desc:   Module for Train object and functions
Filename: Train.cpp
-----------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

#include "Train.h"

namespace sdds {

	void Train::setSafeEmptyState() {
		name[0] = '\0';						// set name member variable to empty string
		numPeople = SAFE_EMPTY_NUM_PEOPLE;	// set number of people to invalid value
		speed = SAFE_EMPTY_SPEED;			// set speed to invalid value
	}

	void Train::set(const char* inputName, int inputNumPeople, double inputSpeed) {
		// validate input
		bool nameIsValid = (inputName != nullptr && strlen(inputName) > 0) ? true : false;
		bool numPeopleIsValid = (inputNumPeople >= 0 && inputNumPeople <= MAX_PEOPLE) ? true : false;
		bool speedIsValid = (inputSpeed >= 0 && inputSpeed <= MAX_SPEED) ? true : false;

		if (nameIsValid && numPeopleIsValid && speedIsValid) {
			strcpy(name, inputName);	// input is validated, set member variables to input
			numPeople = inputNumPeople;
			speed = inputSpeed;
		} else {
			setSafeEmptyState();		// set member variables to safe empty state
		}
	}

	int Train::getNumberOfPeople() const {
		return numPeople;
	}

	const char* Train::getName() const {
		return name;
	}

	double Train::getSpeed() const {
		return speed;
	}

	bool Train::isSafeEmpty() const {
		bool result = false;

		// check if member variables are set to safe empty values
		bool nameIsSafeEmpty = (name[0] == '\0') ? true : false;
		bool numPeopleIsSafeEmpty = (numPeople == SAFE_EMPTY_NUM_PEOPLE) ? true : false;
		bool speedIsSafeEmpty = (speed == SAFE_EMPTY_SPEED) ? true : false;

		if (nameIsSafeEmpty && numPeopleIsSafeEmpty && speedIsSafeEmpty) {
			result = true;	// if all member variables are safe empty return true
		}

		return result;
	}

	void Train::display() const {

		if (!Train::isSafeEmpty()) {	// check if object is empty

			int oldPrecision = cout.precision();
			cout << "NAME OF THE TRAIN : " << name << endl;			// print name
			cout << "NUMBER OF PEOPLE  : " << numPeople << endl;	// print number of people
			cout << "SPEED             : ";
			cout.setf(ios::fixed);						// set fixed format
			cout.precision(DISPLAY_SPEED_PRECISION);	// change precision for speed display
			cout << speed << " km/h" << endl;			// print speed
			cout.unsetf(ios::fixed);					// unset fixed format
			cout.precision(oldPrecision);				// change precision back
		} else {
			cout << "Safe Empty State!" << endl;		// print safe empty state message
		}
	}

	bool Train::loadPeople(int addNumPeople) {
		bool result = false;	// operation success/fail flag
		int newNumPeople = 0;

		if (!isSafeEmpty()) {	// check if train contains valid values
			newNumPeople = numPeople + addNumPeople;	// calculate new number of people in train

			if (newNumPeople >= 0 && newNumPeople <= MAX_PEOPLE) {	// check if new number of people is valid
				numPeople = newNumPeople;	// set new value to instance variable
				result = true;
			}
		}

		return result;
	}


	bool Train::changeSpeed(double addSpeed) {
		bool result = false;	// operation success/fail flag
		double newSpeed = 0;

		if (!isSafeEmpty()) {	// check if train contains valid values
			newSpeed = speed + addSpeed;	// calculate new speed

			if (newSpeed >= 0 && newSpeed <= MAX_SPEED) {	// check if new speed is valid
				speed = newSpeed;	// set new value to instance variable
			}
		}

		return result;
	}

	int transfer(Train first, Train second) {
		int numPeopleMoved = -1;	// operation success/fail flag
		int numPeopleToMove = 0;
		int numInFirst = 0;
		int numInSecond = 0;
		int spaceInFirst = 0;
		bool load1;
		bool load2;

		if (!first.isSafeEmpty() && !second.isSafeEmpty()) {	// only proceed if neither Train is in safe empty state

			numInFirst = first.getNumberOfPeople();		// get number of people in first train
			numInSecond = second.getNumberOfPeople();	// get number of people in second train

			spaceInFirst = MAX_PEOPLE - numInFirst;		// calculate space availability in first train
			numPeopleToMove = spaceInFirst < numInSecond ? spaceInFirst : numInSecond;	// number of people to move is the smaller number between the two

			load1 = first.loadPeople(numPeopleToMove);
			load2 = second.loadPeople(numPeopleToMove*-1);

			if (load1 && load2) {	// check if operation succeeded
				numPeopleMoved = numPeopleToMove;
			} else {
				cout << "Unexpected error in Train.cpp- transfer" << endl;	// this should never occur
			}

		}

		return numPeopleMoved;
	}
}