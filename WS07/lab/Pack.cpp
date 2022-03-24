/* ------------------------------------------------------
Workshop 7 part 1
Module: Pack
Filepack: Pack.cpp
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define  _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "Pack.h"
using namespace std;

namespace sdds {
	// public member functions

	Pack::Pack(const char content[], int size, int unitSize, int numUnits) : Container(content, size * unitSize, numUnits * unitSize) {
		if (unitSize > 0) {
			m_unitSize = unitSize;
		} else {
			setEmpty();
			m_unitSize = 0;
		}
	}

	int Pack::operator+=(int value) {
		return Container::operator+=(value * m_unitSize) / m_unitSize;
	}

	int Pack::operator-=(int value) {
		return Container::operator-=(value * m_unitSize) / m_unitSize;
	}

	int Pack::unit() const {
		return m_unitSize;
	}

	int Pack::noOfUnits() const {
		return Container::volume() / m_unitSize;
	}

	int Pack::size() const {
		return Container::capacity() / m_unitSize;
	}

	void Pack::clear(int packSize, int unitSize, const char content[]) {
		if (unitSize > 0) {
			Container::clear(packSize * unitSize, content);
			m_unitSize = unitSize;
		}
	}

	ostream& Pack::print(ostream& ostr) const {
		if (m_unitSize > 0) {	// check if current object is valid
			Container::print(ostr);
			ostr << ", ";
			ostr << noOfUnits();
			ostr << " in a pack of ";
			ostr << size();
		}
		return ostr;
	}

	istream& Pack::read(istream& istr) {
		int input = 0;
		bool inputValid = false;
		int added = 0;
		int missingUnits = 0;

		if (Container::operator bool()) {	// check if container is valid
			missingUnits = size() - noOfUnits();

			if (missingUnits) {

				cout << "Add to ";
				print(cout) << endl << "> ";

				istr >> input;	// store user input

				if (!istr.fail()) {	// check if an integer was entered
					// an integer was stored
					if (input >= 1 && input <= missingUnits) {
						inputValid = true;
					} else {
						// integer is out of range
						cout << "Value out of range [1<=val<=" << missingUnits << "]: ";
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
						if (input >= 1 && input <= missingUnits) {
							inputValid = true;
						} else {
							// integer is out of range
							cout << "Value out of range [1<=val<=" << missingUnits << "]: ";
						}
					} else {
						// an integer was not entered
						cout << "Invalid Integer, retry: ";
					}
				}

				// add to pack object
				added = (*this += input);

				// display amount added
				cout << "Added " << added << endl;
				istr.ignore(1000, '\n');
			} else {
				cout << "Pack is full!, press <ENTER> to continue...";
				istr.ignore(1000, '\n');
			}
		} else {
			cout << "Broken Container, adding aborted! Press <ENTER> to continue....";
			istr.ignore(1000, '\n');
		}
		return istr;
	}

	// helper functions

	ostream& operator<<(ostream& ostr, const Pack& packObject) {
		return packObject.print(ostr);
	}

	istream& operator>>(istream& istr, Pack& packObject) {
		return packObject.read(istr);
	}
}