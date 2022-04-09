/* ------------------------------------------------------
Final Project Milestone 5
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
#include "Perishable.h"
using namespace std;
namespace sdds {
	// private member functions

	unsigned int AidMan::menu() const {
		int year = 0;
		int month = 0;
		int day = 0;

		ut.getSystemDate(&year, &month, &day);	// get date
		Date currentDate(year, month, day);		// create date object

		cout << "Aid Management System" << endl;
		cout << "Date: ";
		currentDate.write(cout) << endl;	// print formatted date

		cout << "Data file: " << (m_filename != nullptr ? m_filename : "No file") << endl;
		cout << "---------------------------------" << endl;

		return m_mainMenu.run();	// run main menu
	}

	bool AidMan::validateFilename(const char* filename) const {
		const int forbiddenSize = 10;
		const char forbiddenChars[forbiddenSize] = "<>:\"/\\|?*";

		bool filenameIsValid = true;
		int filenameLen = static_cast<int>(strlen(filename));

		if (filenameLen) {
			// set flag to false if any character is a forbidden character
			for (int i = 0; i < filenameLen && filenameIsValid; i++) {	// go through every char in this string
				// go through all forbidden characters
				for (int k = 0; k < forbiddenSize-1 && filenameIsValid; k++) {
					if (filename[i] == forbiddenChars[k]) {
						filenameIsValid = false;	// exit out of both loops
					}
				}
			}
		} else {
			filenameIsValid = false;
		}
		return filenameIsValid;
	}

	void AidMan::save() const {
		ofstream ofs;

		if (m_filename != nullptr) {
			// create/open file for writing
			ofs.open(m_filename);

			for (int i = 0; i < m_iProductNum; i++) {
				m_iProducts[i]->save(ofs);
			}

			// close file
			if (ofs.is_open()) {
				ofs.close();
			}
		}
	}

	void AidMan::deallocate() {
		// dealloc memory for each iProduct object
		for (int i = 0; i < m_iProductNum; i++) {
			delete m_iProducts[i];
			m_iProducts[i] = nullptr;
		}
		m_iProductNum = 0;

		delete [] m_filename;	// dealloc memory for filname char array
		m_filename = nullptr;
	}

	int AidMan::list(const char* sub_desc) {
		char* rowNumInputStr = nullptr;
		int rowNum = 0;
		int printedIndexes[sdds_max_num_items];	// stores indexes of all objects printed
		int numPrinted = 0;
		bool validInput = false;

		// print list header
		cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
		cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

		if (sub_desc == nullptr) {
			// print all items
			for (int i = 0; i < m_iProductNum; i++) {
				cout << setw(4) << i+1 << " | ";		// print row number
				m_iProducts[i]->linear(true);			// set to linear
				m_iProducts[i]->display(cout) << endl;	// print item
				printedIndexes[numPrinted++] = i;
			}
		} else {
			// print only the items containing the sub_desc in their description
			for (int i = 0; i < m_iProductNum; i++) {
				if (*m_iProducts[i] == sub_desc) {
					cout << setw(4) << i+1 << " | ";		// print row number
					m_iProducts[i]->linear(true);			// set to linear
					m_iProducts[i]->display(cout) << endl;	// print item
					printedIndexes[numPrinted++] = i;
				}
			}
		}

		cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

		if (numPrinted) {
			// prompt user to press <ENTER> or input an int between 1 and number of records printed
			// validInput flag is true if they do one of the above
			// if they make an invalid input, keep prompting them
			while (!validInput) {
				cout << "\nEnter row number to display details or <ENTER> to continue:\n>";
				ut.getcstring(rowNumInputStr);		// if user just pressed enter rowNumInput will be set to nullptr

				if (rowNumInputStr != nullptr) {
					// convert user input to integer
					// will convert to 0 if failed
					rowNum = atoi(rowNumInputStr);

					// check if user input number is a valid item in list
					if (rowNum >= 1 && rowNum <= numPrinted) {
						// user entered an int between 1 and num records printed
						validInput = true;	// exit loop
						// display the selected item in a non-linear format
						m_iProducts[printedIndexes[rowNum-1]]->linear(false);
						m_iProducts[printedIndexes[rowNum-1]]->display(cout) << endl << endl;
					}
				} else {
					// user pressed <ENTER>
					validInput = true;	// exit loop
				}
			}
		} else {
			cout << "The list is emtpy!" << endl;
		}
		return numPrinted;
	}

	bool AidMan::load() {
		ifstream ifs;
		ofstream ofs;
		int selection = 0;
		char ch = 0;
		bool filenameValid = false;

		save();			// Saves all the already existing m_iProducts
		deallocate();	// Deallocates all the resources of the AidMan class making it ready to load new information

		// keep prompting for file name until a valid one is entered
		while (!filenameValid) {
			cout << "Enter file name: ";
			ut.getcstring(m_filename);

			// check that get filename worked
			// if it did not work prompt user again
			if (m_filename != nullptr) {
				if (static_cast<int>(strlen(m_filename))) {
					// trim leading and trailing spaces and set tabs, \n, to ' '
					// filename set to nullptr if filename only has spaces
					ut.formatCstring(m_filename);

					if (m_filename != nullptr) {
						// check filename for forbidden characters
						filenameValid = validateFilename(m_filename);
					}
				}
			}
			if (!filenameValid) {
				cout << "Invalid file name!" << endl;
			}
		}

		// got filename, proceed to read from file and load items
		ifs.open(m_filename);	// opens file for reading

		if (!ifs.fail()) {
			// go through each line in file and store each as an item/perishable
			// continue until invalid record is found
			while (!ifs.fail() && !ifs.eof()) {
				// get first character
				ch = ifs.peek();

				if (isdigit(ch)) {
					// check if iProduct array has room to load the item/perishable
						if (ch == '1') {
							// perishable
							m_iProducts[m_iProductNum] = new Perishable();	// create a new Perishable item in the next available iProduct Pointers element
						} else {
							// item
							m_iProducts[m_iProductNum] = new Item();		// create a new Item in the next available iProduct Pointers element
						}

						// load data from file stream into object
						// since load function is virtual, dynamic binding will occur
						m_iProducts[m_iProductNum]->load(ifs);

						// check if item/perishable was loaded succesfully (in good state)
						if (m_iProducts[m_iProductNum]) {
							m_iProductNum++;	// increase iProduct counter
						} else {
							// item was not loaded sucessfully
							delete m_iProducts[m_iProductNum];	// delete item
							m_iProducts[m_iProductNum] = nullptr;
						}
				} else {
					// invalid record found in file
					ifs.setstate(ios::failbit);		// set stream to fail state, this quits the loop
				}
			}
			
			// print result from load
			cout << m_iProductNum << " records loaded!" << endl;

		} else {
			// opening stream was unsuccessful
			cout << "Failed to open " << m_filename << " for reading!" << endl;
			selection = ut.getint(0, 1, "Would you like to create a new data file?\n1- Yes!\n0- Exit\n");
			// create empty file
			if (selection == 1) {
				ofs.open(m_filename);
				if (!ofs.is_open()) {
					ofs.close();
				}
			}
		}

		// close stream
		if (!ifs.is_open()) {
			ifs.close();
		}

		// return true if num items loaded > 0
		return m_iProductNum ? true : false;
	}

	// public member functions

	AidMan::AidMan() : m_mainMenu{NUM_MENU_OPTIONS, "1- List Items\n2- Add Item\n3- Remove Item\n4- Update Quantity\n5- Sort\n6- Ship Items\n7- New/Open Aid Database\n---------------------------------\n"} {
		m_filename = nullptr;
		m_iProductNum = 0;
	}

	AidMan::~AidMan() {
		deallocate();
	}

	void AidMan::run() {
		unsigned int userSelection = 0;

		userSelection = menu();		// run menu and store user selection, selection will be from 0 to NUM_MENU_OPTIONS

		while (userSelection != 0) {

			// if selection is not 0 and filename is null change the selection to 7
			if (m_filename == nullptr) {
				userSelection = 7;
			}

			// user made a selection
			// run the function associated with user selection

			// print menu item that was just selected
			cout << "\n****";
			m_mainMenu.printMenuOptionNameByNumber(cout, userSelection) << "****" << endl;

			switch (userSelection) {
			case 1:		// 1- List Items
				list(nullptr);
				break;
			case 2:		// 2- Add Item
				cout << "this is not implemented yet" << endl;
				break;
			case 3:		// 3- Remove Item
				cout << "this is not implemented yet" << endl;
				break;
			case 4:		// 4- Update Quantity
				cout << "this is not implemented yet" << endl;
				break;
			case 5:		// 5- Sort
				cout << "this is not implemented yet" << endl;
				break;
			case 6:		// 6- Ship Items
				cout << "this is not implemented yet" << endl;
				break;
			case 7:		// 7- New/Open Aid Database
				load();
				break;
			default:
				cout << "Unexpected error in run" << endl;
				break;
			}

			cout << endl;

			userSelection = menu();		// run menu and store user selection again
		}

		// the while loop ended so the user chose to quit
		cout << "Exiting Program!" << endl;		// print ending message

		// save data file here

	}
}