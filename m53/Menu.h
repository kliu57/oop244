/* ------------------------------------------------------
Final Project Milestone 5
Module: Menu
Filename: Menu.h
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_MENU_H
#define SDDS_MENU_H
#include <iostream>
namespace sdds {
    const int MAX_OPTIONS = 15;
    class Menu {
        char* m_menuContent;      // contains the list of options the user can select from
        unsigned int m_options;

    public:
        // constructors
        Menu(unsigned int numOptions, const char menuContent[]);

        // prohibit copying and copy assigning
        Menu(const Menu& source) = delete;
        Menu& operator=(const Menu& source) = delete; 

        // destructor
        ~Menu();

        // Display menu and prompt for user to enter an integer between 0 and m_options
        // Continue to prompt the user until a valid input is received and return that integer
        unsigned int run() const;

        // Print menu option that matches option number in argument
        std::ostream& printMenuOptionNameByNumber(std::ostream& ostr, unsigned int optionNum) const;
    };
}
#endif // !SDDS_MENU_H