/* ------------------------------------------------------
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
Date    Thu Feb 10 2022

Workshop 4 part 1
Module: CarInventory
Desc:   Module for CarInventory object and functions
Filename: CarInventory.cpp
-----------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

#include "CarInventory.h"

namespace sdds {

	void CarInventory::resetInfo() {
		m_type = nullptr;
		m_brand = nullptr;
		m_model = nullptr;
		m_year = 0;
		m_code = 0;
		m_price = 0;
	}

	void CarInventory::deallocMemory() {
		delete [] m_type;
		m_type = nullptr;
		delete [] m_brand;
		m_brand = nullptr;
		delete [] m_model;
		m_model = nullptr;
	}

	bool CarInventory::validateCarInfo(const char* type, const char* brand, const char* model, int year, int code, double price) const {
		bool result = false;

		// checks if all car info information pass validation
		if (type != nullptr &&
			brand != nullptr &&
			model != nullptr &&
			year >= MIN_YEAR &&
			code >= MIN_CODE && code <= MAX_CODE &&
			price > 0
			) {
			result = true;
		}

		return result;
	}

	CarInventory::CarInventory() {
		resetInfo();		// set member variables to safe empty state
	}

	CarInventory::CarInventory(const char* type, const char* brand, const char* model, int year, int code, double price) {
		
		if (validateCarInfo(type, brand, model, year, code, price)) {	// check if arguments are valid
			// set member variables to arguments
			
			m_type = new char[strlen(type)+1];		// allocate dynamic memory for type based on length of argument string
			strcpy(m_type, type);					// copy argument value to address of newly allocated memory

			m_brand = new char[strlen(brand)+1];	// allocate dynamic memory for brand based on length of argument string
			strcpy(m_brand, brand);					// copy argument value to address of newly allocated memory

			m_model = new char[strlen(model)+1];	// allocate dynamic memory for model based on length of argument string
			strcpy(m_model, model);					// copy argument value to address of newly allocated memory

			m_year = year;
			m_code = code;
			m_price = price;

		} else {	// argument(s) are not valid
			resetInfo();		// set member variables to safe empty state
		}
	}

	CarInventory::~CarInventory() {
		deallocMemory();
	}

	bool CarInventory::isValid() const {
		// check if member variables pass validation
		return validateCarInfo(m_type, m_brand, m_model, m_year, m_code, m_price);
	}

	char* CarInventory::getType() const {
		return m_type;
	}

	char* CarInventory::getBrand() const {
		return m_brand;
	}

	char* CarInventory::getModel() const {
		return m_model;
	}

	int CarInventory::getYear() const {
		return m_year;
	}

	CarInventory& CarInventory::setInfo(const char* type, const char* brand, const char* model, int year, int code, double price) {
		deallocMemory();	// deallocate memory

		if (validateCarInfo(type, brand, model, year, code, price)) {	// check if arguments are valid
			// set member variables to arguments

			m_type = new char[strlen(type)+1];		// allocate dynamic memory for type based on length of argument string
			strcpy(m_type, type);					// copy argument value to address of newly allocated memory

			m_brand = new char[strlen(brand)+1];	// allocate dynamic memory for brand based on length of argument string
			strcpy(m_brand, brand);					// copy argument value to address of newly allocated memory

			m_model = new char[strlen(model)+1];	// allocate dynamic memory for model based on length of argument string
			strcpy(m_model, model);					// copy argument value to address of newly allocated memory

			m_year = year;
			m_code = code;
			m_price = price;

		} else {	// argument(s) are not valid
			resetInfo();		// set member variables to safe empty state
		}

		return *this;
	}

	void CarInventory::printInfo() const {
		streamsize oldPrecision = cout.precision();	// save precision

		cout.setf(ios::left);	// set left align
		cout << "| ";

		cout.width(10);
		cout << m_type;			// print type

		cout << " | ";

		cout.width(16);
		cout << m_brand;		// print brand

		cout << " | ";

		cout.width(16);
		cout << m_model;		// print model

		cout << " | ";

		cout.unsetf(ios::left);	// unset left align

		cout.width(4);
		cout << m_year;			// print year

		cout << " | ";

		cout.width(4);
		cout << m_code;			// print code

		cout << " | ";

		cout.setf(ios::fixed);	// set fixed format
		cout.precision(2);		// change precision to two decimal places

		cout.width(9);
		cout << m_price;		// print price

		cout.unsetf(ios::fixed);		// unset fixed format
		cout.precision(oldPrecision);	// change precision back
		cout << " |" << endl;
	}

	bool CarInventory::isSimilarTo(const CarInventory& car) const {
		bool match = false;

		// check if both instances are valid
		if (isValid() && car.isValid()) {
			// compare type, brand, model, year of the two instances
			if (!strcmp(m_type, car.getType()) &&
				!strcmp(m_brand, car.getBrand()) &&
				!strcmp(m_model, car.getModel()) &&
				m_year == car.getYear()
			) {
				match = true;
			}
		}

		return match;
	}

	// check whether there are duplicate entries in the entire inventory
	// returns true if it finds two CarInventory objects that have similar information in the car array
	bool find_similar(CarInventory car[], const int num_cars) {
		bool matchFound = false;

		for (int i = 0; i < num_cars; i++){
			for (int k = i+1; k < num_cars; k++){
				if (car[i].isSimilarTo(car[k])) {
					matchFound = true;
					k = num_cars;	// quit loop
					i = num_cars;	// quit loop
				}
			}
		}

		return matchFound;
	}
}