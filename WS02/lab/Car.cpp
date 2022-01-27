/* ------------------------------------------------------
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
Date    Thu Jan 27 2020

Workshop 2 part 1
Module: Car
Desc:   Module that hold information for passing car
Filename: Car.cpp
-----------------------------------------------------------*/

#include <cstdio>
#include <iostream>
using namespace std;

#include "Car.h"
#include "cStrTools.h"

namespace sdds {

	int allocationSize;		// holds memory allocation and expansion size
	int numCars;			// hold number of cars currently in dynamic array
	int carArraySize;		// current allocation size of array
	Car* carPtr = nullptr;	// holds dynamic array of cars

	void VBPLE_Title() {
		cout << "Vehicle Border Passing Log Entry" << endl;
		cout << "Enter the data in the following format:" << endl;
		cout << "Make and model,LicensePlate,MilitaryTime<ENTER>" << endl;
		cout << "Exit the program by entering the following:" << endl;
		cout << "X,<ENTER>" << endl;
	}

	void initialize(int allocSize) {
		numCars = 0;
		carArraySize = allocSize;
		allocationSize = allocSize;
		carPtr = new Car[allocationSize];	// allocate dynamic memory
	}

	void deallocate(Car& C) {
		delete [] C.makeAndModel;			// deallocate dynamic memory
		C.makeAndModel = nullptr;
	}

	bool read(Car& C) {

		bool carRead = false;	// read success or fail flag
		char makeAndModel[MAX_MAKE_AND_MODEL_LEN+1];
		int makeAndModelLen = 0;
		char timeStr[5];

		read(makeAndModel, MAX_MAKE_AND_MODEL_LEN, ',');	// read user input make and model

		makeAndModelLen = strLen(makeAndModel);		// length of user input

		if (strCmp(makeAndModel, "X") != 0) {	// proceed if input is not X

			carRead = true;
			C.makeAndModel = new char[makeAndModelLen+1];    // allocate dynamic memory

			strCpy(C.makeAndModel, makeAndModel);	// set Car object make and model to a value

			read(C.plate, MAX_PLATE_LEN, ',');	// read license plate from input

			cin >> C.time;	// store time from input
		}

		return carRead;	// return flag
	}

	void print(const Car& C) {
		cout << C.time << ":";
		cout << C.makeAndModel << ", ";
		cout << C.plate << endl;
	}

	void record(const Car& C) {

		int newCarArraySize = 0;

		if (numCars == carArraySize) {	// check if car array is full

			Car* newCarPtr = nullptr;

			newCarArraySize = carArraySize + allocationSize;

			newCarPtr = new Car[newCarArraySize];     // allocate dynamic memory

			// copy all the cars from old to new array
			for (int i = 0; i < carArraySize; i++) {

				//newCarPtr[i].makeAndModel = carPtr[i].makeAndModel;
				//strCpy(newCarPtr[i].plate, carPtr[i].plate);
				//newCarPtr->time = carPtr->time;

				newCarPtr[i] = carPtr[i];
			}

			delete [] carPtr;	// deallocate memory of old array
			carPtr = newCarPtr;
			carArraySize = newCarArraySize;
		}

		// add new car from argument
		carPtr[numCars].makeAndModel = C.makeAndModel;
		strCpy(carPtr[numCars].plate, C.plate);
		carPtr[numCars].time = C.time;
		numCars++;	// update num of cars currently in array
	}

	void endOfDay() {
		for (int i = 0; i < numCars; i++) {	
			print(carPtr[i]);		// print every car record
			deallocate(carPtr[i]);	// deallocate dynamic memory for every car make and model
		}

		delete [] carPtr;	// deallocate dynamic memory for array of cars
		carPtr = nullptr;
	}
}