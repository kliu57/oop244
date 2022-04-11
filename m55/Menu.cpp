/* ------------------------------------------------------
Final Project Milestone 5
Module: Menu
Filename: Menu.cpp
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define  _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "Menu.h"
#include "Utils.h"
using namespace std;
namespace sdds {
	// public member functions

	Menu::Menu(unsigned int numOptions, const char menuContent[]) {
		// set to invalid state to begin with
		m_menuContent = nullptr;
		m_options = numOptions;

		// validate argument
		if (numOptions <= MAX_OPTIONS) {
			ut.alocpy(m_menuContent, menuContent);	// allocate new memory storage, copy data to newly allocated memory location
		}
	}

	Menu::~Menu() {
		delete [] m_menuContent;
	}

	unsigned int Menu::run() const {
		cout << m_menuContent << "0- Exit" << endl;					// print menu
		return ut.getint(0, m_options, "> ", "Invalid Integer");	// prompt for user to enter an integer between 0 and m_options
	}

	ostream& Menu::printMenuOptionNameByNumber(ostream& ostr, unsigned int optionNum) const {
		unsigned int currentMenuOption = 1;
		bool success = false;
		int spaceIndex = -1;
		int menuContentLength = static_cast<int>(strlen(m_menuContent));

		// go through every character in m_menuContent
		// Each \n in m_menuContent indicates a new menu option
		for (int i = 0; i < menuContentLength; i++) {
			
			// if current menu option matches the argument option, print the menu option and end loop
			if (currentMenuOption == optionNum) {

				// find first space
				for (int k = i; k < menuContentLength && m_menuContent[k] != '\n'; k++) {
					if (m_menuContent[k] == ' ') {
						spaceIndex = k;
						k = menuContentLength;	// quit loop
					}
				}

				if (spaceIndex != -1) {
					// print every character after space until newline or end of string
					for (int m = spaceIndex+1; m < menuContentLength && m_menuContent[m] != '\n'; m++) {
						ostr << m_menuContent[m];
					}
					success = true;
				}

				i = menuContentLength;	// quit loop
			}

			// check if character is newline
			if (m_menuContent[i] == '\n') {
				currentMenuOption++;	// increase menu option counter to indicate a new menu option reached
			}
		}

		if (!success) {
			// print not found if nothing was printed
			ostr << "menu option not found";
		}

		return ostr;
	}
}