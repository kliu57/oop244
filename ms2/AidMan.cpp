/* ------------------------------------------------------
Final Project Milestone 2
Module: AidMan
Filename: AidMan.cpp
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define  _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iomanip>
#include "AidMan.h"
#include "Utils.h"
#include "Date.h"
using namespace std;
namespace sdds {
	// private member functions

	unsigned int AidMan::menu() const {
		int year = 0;
		int month = 0;
		int day = 0;

		ut.getSystemDate(&year, &month, &day);	// get date
		Date currentDate(year, month, day);		// create date object

		cout << "Aid Management System Version 0.1" << endl;
		cout << "Date: ";
		currentDate.write(cout) << endl;	// print formatted date

		cout << "Data file: " << (m_filename != nullptr ? m_filename : "No file") << endl;
		cout << "---------------------------------" << endl;

		return m_mainMenu.run();	// run main menu
	}

	// public member functions

	AidMan::AidMan() : m_mainMenu{NUM_MENU_OPTIONS, "1- List Items\n2- Add Item\n3- Remove Item\n4- Update Quantity\n5- Sort\n6- Ship Items\n7- New/Open Aid Database\n---------------------------------\n"} {
		m_filename = nullptr;
	}

	AidMan::~AidMan() {
		delete [] m_filename;
	}

	void AidMan::run() const {
		unsigned int userSelection = 0;

		userSelection = menu();		// run menu and store user selection, selection will be from 0 to NUM_MENU_OPTIONS

		while (userSelection != 0) {
			cout << endl << "****";
			m_mainMenu.printMenuOptionNameByNumber(cout, userSelection);	// print menu item that was just selected and stored
			cout << "****" << endl << endl;

			userSelection = menu();		// run menu and store user selection again
		}

		// the while loop ended so the user chose to quit
		cout << "Exiting Program!" << endl;		// print ending message
	}
}