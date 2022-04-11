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
		int filenameLen = 0;
		
		if (filename != nullptr) {
			filenameLen = static_cast<int>(strlen(filename));
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
				ofs << endl;
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

	// menu item 1
	int AidMan::list(const char* sub_desc) {
		int rowNum = 0;
		int storedIndexes[sdds_max_num_items];	// stores indexes of all objects to be printed
		int numProducts = 0;	// stores number of total products to be printed

		// First store all indexes of items to be printed
		if (sub_desc == nullptr) {
			// print all items
			for (int i = 0; i < m_iProductNum; i++) {
				storedIndexes[numProducts++] = i;		// store index
			}
		} else {
			// print only the items containing the sub_desc in their description
			for (int i = 0; i < m_iProductNum; i++) {
				if (*m_iProducts[i] == sub_desc) {
					storedIndexes[numProducts++] = i;		// store index
				}
			}
		}

		// If there are more than zero stored indexes, print them
		if (numProducts) {
			cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

			// go through each index and print the item
			for (int i = 0; i < numProducts; i++) {
				cout << setw(4) << storedIndexes[i]+1 << " | ";			// print row number which is index+1
				m_iProducts[storedIndexes[i]]->linear(true);			// set to linear
				m_iProducts[storedIndexes[i]]->display(cout) << endl;	// print item
			}

			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

			// prompt user to press <ENTER> or input an int between 1 and number of records printed
			// result is -1 if they press <ENTER>
			rowNum = ut.getintOrEnter(1, numProducts, "Enter row number to display details or <ENTER> to continue:\n> ", "Invalid entry!\nEnter row number to display details or <ENTER> to continue:\n> ");

			if (rowNum != -1) {
				if (rowNum >= 1 && rowNum <= numProducts) {
					// display the selected item in a non-linear format
					m_iProducts[storedIndexes[rowNum-1]]->linear(false);
					m_iProducts[storedIndexes[rowNum-1]]->display(cout) << endl;
				} else{
					cout << "Unexpected error in list " << rowNum << endl;
				}
			}
		} else {
			cout << "The list is emtpy!" << endl;
		}

		return numProducts;
	}

	// menu item 2
	void AidMan::addItem() {
		int selection = 0;
		int sku = 0;
		iProduct* newProduct = nullptr;

		// check if array of iProduct pointers is full
		if (m_iProductNum < sdds_max_num_items) {
			// prompt user to enter item type
			selection = ut.getint(0, 2, "1- Perishable\n2- Non-Perishable\n-----------------\n0- Exit\n> ", "Invalid Integer");

			if (selection) {
				// create item based on user selection of type
				if (selection == 1) {	// perishable
					newProduct = new Perishable();
				} else {	// non-perishable
					newProduct = new Item();
				}

				sku = newProduct->readSku(cin);	// read sku from console

				// check if sku is already present in database
				if (search(sku) == -1) {	// sku not present in DB
					// sku is not in the database, read the rest of the item details
					newProduct->read(cin);

					// check if read product is in good state
					if (*newProduct) {
						// add product pointer to array of pointers
						m_iProducts[m_iProductNum++] = newProduct;
					} else {
						// display product and delete it
						newProduct->display(cout) << endl;
						delete newProduct;
					}
				} else {	// sku already present in DB
					delete newProduct;	// delete new product since its a duplicate
					cout << "Sku: " << sku << " is already in the system, try updating quantity instead.\n";
				}
			} else {
				// user chooses to exit
				cout << "Aborted\n";
			}
		} else {
			cout << "Database full!\n";
		}
	}

	// menu item 3
	void AidMan::removeItem() {
		int sku = 0;
		int index = 0;
		char* desc = nullptr;	// alloc temp memory to this variable
		int confirmation = 0;
		int storedIndexes[sdds_max_num_items];	// stores indexes of all objects to be printed
		int numProducts = 0;	// stores number of total products printed

		ut.getcstring(desc, "Item description: ", "Invalid description");	// get desc from user input

		// store indexes of the items containing the desc in their description
		for (int i = 0; i < m_iProductNum; i++) {
			if (*m_iProducts[i] == desc) {
				storedIndexes[numProducts++] = i;		// store index
			}
		}

		// If there are more than zero stored indexes, print them
		if (numProducts) {
			cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

			// go through each index and print the item
			for (int i = 0; i < numProducts; i++) {
				cout << setw(4) << storedIndexes[i]+1 << " | ";			// print row number which is index+1
				m_iProducts[storedIndexes[i]]->linear(true);			// set to linear
				m_iProducts[storedIndexes[i]]->display(cout) << endl;	// print item
			}

			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

			// prompt user to input an SKU
			sku = ut.getint(10000, 99999, "Enter SKU: ", "Invalid Integer");
			index = search(sku);	// get index in array of pointers that points at object with this sku

			if (index != -1) {
				// item with this sku exists in database
				// print item and confirmation message and menu
				cout << "Following item will be removed: \n";
				m_iProducts[index]->linear(false);				// set to descriptive format
				m_iProducts[index]->display(cout) << endl;		// display item

				// prompt user for confirmation
				confirmation = ut.getint(0, 1, "Are you sure?\n1- Yes!\n0- Exit\n> ", "Invalid Integer");

				if (confirmation) {
					remove(index);	// remove item
					cout << "Item removed!\n";
				} else {
					cout << "Aborted!\n";
				}
			} else {
				cout << "SKU not found!\n";
			}
		} else {
			cout << "No matches found!\n";
		}

		delete [] desc;	// dealloc temp memory
	}

	// menu item 4
	void AidMan::updateQuantity() {
		int sku = 0;
		int index = 0;
		char* desc = nullptr;	// alloc temp memory to this variable
		int confirmation = 0;
		int storedIndexes[sdds_max_num_items];	// stores indexes of all objects to be printed
		int numProducts = 0;	// stores number of total products printed
		int spaceForAdd = 0;
		int amountForRemove = 0;
		int toAdd = 0;
		int toRemove = 0;

		ut.getcstring(desc, "Item description: ", "Invalid description");	// get desc from user input

		// store indexes of the items containing the desc in their description
		for (int i = 0; i < m_iProductNum; i++) {
			if (*m_iProducts[i] == desc) {
				storedIndexes[numProducts++] = i;		// store index
			}
		}

		// If there are more than zero stored indexes, print them
		if (numProducts) {
			cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

			// go through each index and print the item
			for (int i = 0; i < numProducts; i++) {
				cout << setw(4) << storedIndexes[i]+1 << " | ";			// print row number which is index+1
				m_iProducts[storedIndexes[i]]->linear(true);			// set to linear
				m_iProducts[storedIndexes[i]]->display(cout) << endl;	// print item
			}

			cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

			// prompt user to input an SKU
			sku = ut.getint(10000, 99999, "Enter SKU: ", "Invalid Integer");
			index = search(sku);	// get index in array of pointers that points at object with this sku

			if (index != -1) {
				// item with this sku exists in database

				// prompt user for add or remove
				confirmation = ut.getint(0, 2, "1- Add\n2- Reduce\n0- Exit\n> ", "Invalid Integer");

				if (confirmation == 1) {
					//add
					if (m_iProducts[index]->qty() >= m_iProducts[index]->qtyNeeded()) {
						cout << "Quantity Needed already fulfilled!\n";
					} else {
						spaceForAdd = m_iProducts[index]->qtyNeeded() - m_iProducts[index]->qty();
						toAdd = ut.getint(1, spaceForAdd, "Quantity to add: ", "Invalid Integer");
						cout << (*m_iProducts[index] += toAdd) << " items added!\n";
					}
				} else if (confirmation == 2) {
					//remove
					if (m_iProducts[index]->qty() == 0) {
						cout << "Quaintity on hand is zero!\n";
					} else {
						amountForRemove = m_iProducts[index]->qty();
						toRemove = ut.getint(1, amountForRemove, "Quantity to reduce: ", "Invalid Integer");
						cout << (*m_iProducts[index] -= toRemove) << " items removed!\n";
					}
				} else {
					cout << "Aborted!\n";
				}
			} else {
				cout << "SKU not found!\n";
			}
		} else {
			cout << "No matches found!\n";
		}

		delete [] desc;	// dealloc temp memory
	}

	// menu item 7
	bool AidMan::load() {
		ifstream ifs;
		ofstream ofs;
		int selection = 0;
		char ch = 0;
		bool filenameValid = false;

		save();			// Saves all the already existing m_iProducts
		deallocate();	// Deallocates all the resources of the AidMan class making it ready to load new information

		// get filename and validate
		ut.getcstring(m_filename, "Enter file name: ", "Invalid filename");  // get filename
		ut.formatCstring(m_filename);	// trim leading/trailing whitespace and set internal tabs and newlines to spaces
		if (m_filename != nullptr) {
			filenameValid = validateFilename(m_filename);	// check filename for forbidden characters
		}

		// keep prompting for filename until a valid one is entered
		while (!filenameValid) {
			// get filename and validate
			ut.getcstring(m_filename, "Invalid filename, retry: ", "Invalid filename");  // get filename
			ut.formatCstring(m_filename);	// trim leading/trailing whitespace and set internal tabs and newlines to spaces
			if (m_filename != nullptr) {
				filenameValid = validateFilename(m_filename);	// check filename for forbidden characters
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
					if (ch == '1' || ch == '2' || ch == '3') {
						// perishable is 10000-39999
						m_iProducts[m_iProductNum] = new Perishable();	// create a new Perishable item in the next available iProduct Pointers element
					} else {
						// item is 40000, 99999
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
			selection = ut.getint(0, 1, "Would you like to create a new data file?\n1- Yes!\n0- Exit\n> ");
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

	int AidMan::search(int sku) const {
		int indexOfMatch = -1;
		for (int i = 0; i < m_iProductNum; i++) {
			if (*m_iProducts[i] == sku) {	// check if item sku matches
				indexOfMatch = i;
			}
		}
		return indexOfMatch;
	}

	void AidMan::remove(int index) {
		if (index >= 0 && index < m_iProductNum) {	// ensure index is valid
			delete m_iProducts[index];	// dealloc memory
			m_iProducts[index] = nullptr;

			// if item is not the last, shift the other ones over
			for (int i = index+1; i < m_iProductNum; i++) {
				m_iProducts[i-1] = m_iProducts[i];	// shift over to the left
				m_iProducts[i] = nullptr;			// set element that was just shifted to nullptr
			}
			m_iProductNum--;	// decrement products counter
		}
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
				addItem();
				break;
			case 3:		// 3- Remove Item
				removeItem();
				break;
			case 4:		// 4- Update Quantity
				updateQuantity();
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

		save();		// save file with contents of the iProduct pointers array
	}
}