/* ------------------------------------------------------
Final Project Milestone 5
Module: AidMan
Filename: AidMan.h
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H
#include <iostream>
#include "Menu.h"
#include "iProduct.h"
namespace sdds {
    const int NUM_MENU_OPTIONS = 7;
    const int sdds_max_num_items = 100;
    class AidMan {
        char* m_filename{};
        Menu m_mainMenu;
        iProduct* m_iProducts[sdds_max_num_items]{};    // array of iProduct pointers
        int m_iProductNum;

        // Returns an unsigned integer that is the user's selection of an option in the main menu of the system
        unsigned int menu() const;

        // Returns true if filename does not contain forbidden characters
		bool validateFilename(const char* filename) const;

        // if the filename attribute is not null
        // Creates an ofstream object using the filename (to write into)
        // then function goes through the iProduct Pointers up to the number of number of iProduct Items and calls the save() of each iProduct to write them in the file.
        // if the filename attribute is null, this function does nothing.
        void save() const;

        // deletes all the dynamic memory allocated in iProduct Pointers elements and the filename, and then sets number of iProduct Items to zero.
        void deallocate();

        // menu item 1
        // prints all items, asks user if they want to see more details
        // returns number of items printed
        int list(const char* sub_desc = nullptr);

        // menu item 2
        // prompt user to choose perishable or non-perishable, then a Perishable or Non-Perishable Item is allocated in an iProduct pointer
        // prompt user for SKU, if SKU not found in existing items, the rest of the data is read from the console
        // If the read iProduct is in a good state, it is added to the next available element of the iProduct Pointers array and number of iProduct Items is added by one
        // otherwise, the allocated Item is displayed and then deleted.
        void addItem();

        // menu item 7
        // Loads data records from a data file and returns true if at least one record is loaded
        bool load();

        // Loops through all the iProduct Pointers elements and if the SKU is a match it will return the index, otherwise it will return -1
        int search(int sku) const;

    public:
        // constructor
        AidMan();

        // prohibit copying and copy assigning
        AidMan(const AidMan& source) = delete;
        AidMan& operator=(const AidMan& source) = delete; 

        // destructor
        ~AidMan();

        // Display menu and prompt for user to enter an integer between 0 and m_options
        // Continue to prompt the user until a valid input is received and return that integer
        void run();
    };
}
#endif // !SDDS_AIDMAN_H