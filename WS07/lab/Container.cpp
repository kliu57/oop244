/* ------------------------------------------------------
Workshop 7 part 1
Module: Container
Filecontainer: Container.h
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define  _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "Container.h"
using namespace std;

namespace sdds {

	// protected member functions

	void Container::setEmpty() {
		m_content[0] = '\0';
		m_capacity = 0;
		m_contentVolume = 0;
	}

	int Container::capacity() const {
		return m_capacity;
	}

	int Container::volume() const {
		return m_contentVolume;
	}

	// public member functions

	Container::Container(const char content[], int capacity, int contentVolume) {
		if (content != nullptr && contentVolume <= capacity) {
			strcpy(m_content, content);
			m_capacity = capacity;
			m_contentVolume = contentVolume;
		} else {
			setEmpty();
		}
	}

	int Container::operator+=(int value) {
		int space = m_capacity - m_contentVolume;	// calculate space remaining
		int amtAdded = 0;
		if (value <= space) {	// check if value fits in space remaining
			// fits, so add full value in
			amtAdded = value;
		} else {
			// does not fit, add until capacity
			amtAdded += space;
		}
		m_contentVolume += amtAdded;	// actual add operation
		return amtAdded;
	}

	int Container::operator-=(int value) {
		int amtDeducted = 0;
		if (value <= m_contentVolume) {	// check if there is enough volume to deduct the arg value
			// deduct the exact arg value
			amtDeducted = value;
		} else {
			// deduct everything in volume
			amtDeducted = m_contentVolume;
		}
		m_contentVolume -= amtDeducted;	// actual deduction operation
		return amtDeducted;
	}

	Container::operator bool() const {
		return (m_content[0] != '\0' && m_contentVolume <= m_capacity) ? true : false;
	}

	void Container::clear(int capacity, const char content[]) {
		setEmpty();	// clear object
		if (capacity > 0 && content != nullptr) {
			if (content[0] != '\0') {
				// set object to new values if validation passed
				strcpy(m_content, content);
				m_capacity = capacity;
				m_contentVolume = 0;
			}
		}
	}

	ostream& Container::print(ostream& ostr) const {
		if (*this) {	// check if current object is valid
			ostr << m_content;
			ostr << ": (";
			ostr << m_contentVolume;
			ostr << "cc/";
			ostr << m_capacity;
			ostr << ")";
		} else {
			ostr << "****: (**cc/***)";
		}
		return ostr;
	}

	istream& Container::read(istream& istr) {
		int input = 0;
		bool inputValid = false;
		int added = 0;

		if (*this) {	// check if container is valid
			cout << "Add to ";
			print(cout) << endl << "> ";

			istr >> input;	// store user input

			if (!istr.fail()) {	// check if an integer was entered
				// an integer was stored
				if (input >= 1 && input <= 999) {
					inputValid = true;
				} else {
					// integer is out of range
					cout << "Value out of range [1<=val<=999]: ";
				}
			} else {
				// an integer was not entered
				cout << "Invalid Integer, retry: ";
			}

			while (!inputValid) {   // user did not enter an integer, keep prompting user for input until valid one is entered
				// clear buffer
				istr.clear();
				istr.ignore(1000, '\n');

				istr >> input;	// store user input

				if (!istr.fail()) {	// check if an integer was stored succesfully
					// an integer was stored
					if (input >= 1 && input <= 999) {
						inputValid = true;
					} else {
						// integer is out of range
						cout << "Value out of range [1<=val<=999]: ";
					}
				} else {
					// an integer was not entered
					cout << "Invalid Integer, retry: ";
				}
			}

			// add to container object
			added = (*this += input);

			// display amount added
			cout << "Added " << added << " CCs" << endl;
			istr.ignore(1000, '\n');
		} else {
			cout << "Broken Container, adding aborted! Press <ENTER> to continue....";
			istr.ignore(1000, '\n');
		}
		return istr;
	}

	// helper functions

	ostream& operator<<(ostream& ostr, const Container& containerObject) {
		return containerObject.print(ostr);
	}

	istream& operator>>(istream& istr, Container& containerObject) {
		return containerObject.read(istr);
	}
}