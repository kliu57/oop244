/* ------------------------------------------------------
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
Date    Sun Mar 6 2022

Workshop 6 part 2
Module: Name
Desc:   Module for Name object and functions
Filename: Name.cpp
-----------------------------------------------------------*/
#define  _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <string>
#include "Name.h"
using namespace std;

namespace sdds {

	// private member functions

	bool Name::containsSpaces(const char* cstring) const {
		bool foundSpace = false;
		int cstringLength = 0;
		if (cstring != nullptr) {
			cstringLength = (int)strlen(cstring);
			for (int i = 0; i < cstringLength && cstring[i] != '\0'; i++) {	// iterate through each character to look for space
				if (isspace(cstring[i])) {
					foundSpace = true;	// space character found
					i = cstringLength;	// quit loop
				}
			}
		}
		return foundSpace;
	}

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

	ostream& Name::printName(ostream& ostr) const {
		ostr << m_fname;	// print first name
		if (m_mname != nullptr) {	// has middle name
			if (m_isShort) {
				ostr << ' ' << m_mname[0] << '.';	// print abbreviated middle name
			} else {
				ostr << ' ' << m_mname;	// print middle name
			}
		}
		if (m_lname != nullptr) {	// has last name
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
			*this = nameObject;
		} else {
			setEmpty();
		}
	}

	Name& Name::operator=(const Name& nameObject) {
		if (this != &nameObject && nameObject) {	// check that addresses are not the same and arg object is valid
			allocateAndCopyFName(nameObject.m_fname);
			allocateAndCopyLName(nameObject.m_lname);
			allocateAndCopyMName(nameObject.m_mname);
			m_isShort = nameObject.m_isShort;
		} else {
			setEmpty();
		}
		return *this;
	}

	Name& Name::operator+=(const char* name) {
		if (validName(name)) {
			if (!containsSpaces(name)) {	// workshop instructions state if there are spaces in the cstring the operation fails
				if (m_fname == nullptr) {
					allocateAndCopyFName(name);
				} else if (m_mname == nullptr) {
					allocateAndCopyMName(name);
				} else if (m_lname == nullptr) {
					allocateAndCopyLName(name);
				} else {
					setEmpty();	// if object already has all three parts set to safe empty state
				}
			} else {
				setEmpty();	// set to safe empty state if cstring contains spaces
			}
		} // if cstring is null or empty the object does not change
		return *this;
	}

	Name::operator bool() const {
		return (m_fname != nullptr) ? true : false;
	}



	void Name::setShort(bool isShort) {
		m_isShort = isShort;
	}

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
		std::string firstWord;
		std::string secondWord;
		std::string thirdWord;
		bool validInput = false;

		if (!isspace(istr.peek())) {
			// read first word
			istr >> firstWord;

			if (istr.peek() == ' ') {
				istr.ignore();	// throw away this character

				if (!isspace(istr.peek())) {
					// read second word
					istr >> secondWord;

					if (istr.peek() == ' ') {
						istr.ignore();	// throw away this character

						if (!isspace(istr.peek())) {
							// read third word
							istr >> thirdWord;

							if (istr.peek() == '\n') {	// three words followed by newline - VALID
								validInput = true;
								istr.clear();
								istr.ignore();
							}
						} else {
							istr.clear();
							if (&istr != &cin) istr.ignore(1000, '\n');
						}
					} else if (istr.peek() == '\n') {	// two words followed by newline - VALID
						validInput = true;
						istr.clear();
						istr.ignore();
					}
				} else {
					istr.clear();
					if (&istr != &cin) istr.ignore(1000, '\n');
				}
			} else if (istr.peek() == '\n') {	// one words followed by newline - VALID
				validInput = true;
				istr.clear();
				istr.ignore();
			}
		} else {
			istr.clear();
			if (&istr != &cin) istr.ignore(1000, '\n');
		}

		if (validInput) {
			if (!thirdWord.empty()) {	// third word has stored data
				set(firstWord.c_str(), thirdWord.c_str(), secondWord.c_str());
			} else if (!secondWord.empty()) {	// second word has stored data
				set(firstWord.c_str(), secondWord.c_str());
			} else {	// only first word has stored data
				set (firstWord.c_str());
			}
			istr.clear();				// clears state to allow further extraction
		} else {
			setEmpty();					// set object to empty
		}

		if (&istr != &cin) {					// if istr is not cin assume it is reading from file
			if (istr.eof()) {					// check if end of stream reached
				istr.setstate(ios::failbit);	// Set the istream into a fail state
			}
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