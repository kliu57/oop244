/* ------------------------------------------------------
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
Date    Tue Mar 01 2022

Workshop 6 part 2
Module: Name
Desc:   Module for Name object and functions
Filename: Name.cpp
-----------------------------------------------------------*/
#define  _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "Name.h"
using namespace std;

namespace sdds {

	// private member functions

	bool Name::validName(const char* name) const {
		bool valid = false;
		int nameLength = 0;
		if (name != nullptr) {
			nameLength = (int)strlen(name);
			for (int i = 0; i < nameLength && name[i] != '\0'; i++) {	// iterate through each character to look for nonspace
				if (!isspace(name[i])) {
					valid = true;	// non-space character found
					i = nameLength;	// quit loop
				}
			}
		}
		return valid;
	}

	void Name::setEmpty() {
		m_isShort = false;
		delete [] m_fname;
		m_fname = nullptr;
		delete [] m_lname;
		m_lname = nullptr;
		delete [] m_mname;
		m_mname = nullptr;
	}

	void Name::allocateAndCopyFName(const char* fname) {
		delete [] m_fname;	// release current memory storage if any
		m_fname = nullptr;
		if (fname != nullptr) {
			m_fname =  new (nothrow) char[strlen(fname)+1];	// allocate new memory storage
			if (m_fname!= nullptr) { 
				strcpy(m_fname, fname);	// copy data to newly allocated memory location
			}
		}
	}

	void Name::allocateAndCopyLName(const char* lname) {
		delete [] m_lname;	// release current memory storage if any
		m_lname = nullptr;
		if (lname != nullptr) {
			m_lname =  new (nothrow) char[strlen(lname)+1];	// allocate new memory storage
			if (m_lname!= nullptr) { 
				strcpy(m_lname, lname);	// copy data to newly allocated memory location
			}
		}
	}

	void Name::allocateAndCopyMName(const char* mname) {
		delete [] m_mname;	// release current memory storage if any
		m_mname = nullptr;
		if (mname != nullptr) {
			m_mname =  new (nothrow) char[strlen(mname)+1];	// allocate new memory storage
			if (m_mname!= nullptr) { 
				strcpy(m_mname, mname);	// copy data to newly allocated memory location
			}
		}
	}

	void Name::extractChar(istream& istr, char ch) const {
		if (istr.peek() == ch) { // checking if the next character in keyboard is same as ch
			istr.ignore();					// throw away this character
		} else {
			istr.ignore(1000, ch);			// throw away everything after or until ch
			istr.setstate(ios::failbit);	// Set the istream into a fail state
		}
	}

	void Name::extractChar(istream& istr, char chA, char chB) const {
		if (istr.peek() == chA || istr.peek() == chB) { // checking if the next character in keyboard is same as ch
			istr.ignore();					// throw away this character
		} else {
			istr.ignore(1000, '\n');			// throw away everything after or until newline
			istr.setstate(ios::failbit);	// Set the istream into a fail state
		}
	}

	ostream& Name::printName(ostream& ostr) const {
		ostr << m_fname;	// print first name
		if (m_lname != nullptr) {
			// has last name
			if (m_mname != nullptr) {
				// has middle name
				if (m_isShort) {
					ostr << ' ' << m_mname[0] << '.';	// print abbreviated middle name
				} else {
					ostr << ' ' << m_mname;	// print middle name
				}
			}
			ostr << ' ' << m_lname;	// print last name
		}
		return ostr;
	}

	void Name::set(const char* fname, const char* lname, const char* mname) {
		allocateAndCopyFName(fname);
		allocateAndCopyLName(lname);
		allocateAndCopyMName(mname);
	}

	// public member functions

	Name::Name() {
		setEmpty();
	}
	Name::Name(const char* fname) {
		if (validName(fname)) {
			m_isShort = false;
			set(fname);
		} else {
			setEmpty();
		}
	}
	Name::Name(const char* fname, const char* lname) {
		if (validName(fname) && validName(lname)) {
			m_isShort = false;
			set(fname, lname);
		} else {
			setEmpty();
		}
	}
	Name::Name(const char* fname, const char* mname, const char* lname) {
		if (validName(fname) && validName(lname) && validName(mname)) {
			m_isShort = false;
			set(fname, lname, mname);
		} else {
			setEmpty();
		}
	}

	Name::~Name() {
		setEmpty();
	}

	// copy constructor
	Name::Name(const Name& nameObject) {
		if (nameObject) {
			allocateAndCopyFName(nameObject.m_fname);
			allocateAndCopyLName(nameObject.m_lname);
			allocateAndCopyMName(nameObject.m_mname);
		} else {
			setEmpty();
		}
	}

	Name& Name::operator+=(const char* name) {
		if (validName(name)) {
			if (m_fname == nullptr) {
				allocateAndCopyFName(name);
			} else if (m_mname == nullptr) {
				allocateAndCopyMName(name);
			} else if (m_lname == nullptr) {
				allocateAndCopyLName(name);
			} else {
				setEmpty();
			}
		}
		return *this;
	}

	Name::operator bool() const {
		return (m_fname != nullptr) ? true : false;
	}

	void Name::setShort(bool isShort) {
		m_isShort = isShort;
	}

	// print to screen or to file
	ostream& Name::print(ostream& ostr, bool toFile) const {
		if (*this) {	// check if current object is valid
			if (toFile) {
				// writing to file
				printName(ostr);
				ostr << '\n';	// add newline after writing one line to file
				ostr.flush();	// refresh file
			} else {
				// not writing to file
				printName(ostr);
			}
		}
		return ostr;
	}

	istream& Name::read(istream& istr) {
		char firstWord[MAX_INPUT_LENGTH+1] = {0};
		char secondWord[MAX_INPUT_LENGTH+1] = {0};
		char thirdWord[MAX_INPUT_LENGTH+1] = {0};
		int firstWordIndex = 0;
		int secondWordIndex = 0;
		int thirdWordIndex = 0;
		char ch = 0;
		unsigned int i = 0;
		bool validInput = true;

		istr.get(ch);	// read first character

		// read first word
		for (i = 0; i < MAX_INPUT_LENGTH && !isspace(ch); i++) {
			firstWord[firstWordIndex++] = ch;	// store
			// read the cString stopping at the size limit
			if (istr.peek() != ' ' && istr.peek() != '\n') {
				if (i < MAX_INPUT_LENGTH-1) {
					istr.get(ch);
				}
			} else {
				i = MAX_INPUT_LENGTH;	// quit loop
			}
		}
		firstWord[firstWordIndex] = 0; // make sure the cString is null terminated

		extractChar(istr, ch);	// extract space or newline

		if (ch == ' ') {
			// read second word
			for (i = i; i < MAX_INPUT_LENGTH && !isspace(ch); i++) {
				secondWord[secondWordIndex++] = ch;
				// read the cString stopping at the size limit
				if (i < MAX_INPUT_LENGTH-1) {
					istr.get(ch); 
				}
			}
			secondWord[secondWordIndex] = 0; // make sure the cString is null terminated

			if (ch == ' ') {
				// read third word
				for (i = i; i < MAX_INPUT_LENGTH && !isspace(ch); i++) {
					thirdWord[thirdWordIndex++] = ch;
					// read the cString stopping at the size limit
					if (i < MAX_INPUT_LENGTH-1) {
						istr.get(ch); 
					}
				}
				thirdWord[thirdWordIndex] = 0; // make sure the cString is null terminated

				if (ch != '\n') {	// a valid input must have newline char following third word
					validInput = false;
					cout <<  "input doesnt have newline char following third word (" << ch << ")" <<endl;
				}
			} else {
				// there is no third word
				if (ch != '\n') {	// a valid input must have newline char following second word
					validInput = false;
					cout <<  "input doesnt have newline char following sec word" << endl;
				}
			}
		} else {
			// there is no second word
			if (ch != '\n') {	// a valid input must have newline char following first word
				validInput = false;
				cout <<  "input doesnt have newline char following 1st word" << endl;
			}
		}

		if (validInput) {
			if (thirdWord[0] != 0) {
				set(firstWord, secondWord, thirdWord);
			} else if (secondWord[0] != 0) {
				set(firstWord, secondWord);
			} else {
				set (firstWord);
			}
			istr.clear();				// clears state to allow further extraction

			cout << "name read!" << endl;
		} else {
			setEmpty();					// set object to empty
			istr.clear();				// clears state to allow further extraction
			//istr.ignore(2000, '\n');	// clears the input buffer

			cout << "name not read!" << endl;
		}
		return istr;
	}

	// helper functions

	ostream& operator<<(ostream& ostr, const Name& nameObject) {
		if (nameObject) {
			nameObject.print(ostr, false);
		} else {
			ostr << "Bad Name";
		}
		return ostr;
	}

	istream& operator>>(istream& istr, Name& nameObject) {
		return nameObject.read(istr);
	}
}