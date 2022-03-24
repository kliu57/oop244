/* ------------------------------------------------------
Final Project Milestone 2
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
namespace sdds {
    const int NUM_MENU_OPTIONS = 7;
    class AidMan {
        char* m_filename;
        Menu m_mainMenu;

        // Returns an unsigned integer that is the user's selection of an option in the main menu of the system
        unsigned int menu() const;

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
        void run() const;
    };
}
#endif // !SDDS_AIDMAN_H