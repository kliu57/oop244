/* ------------------------------------------------------
Workshop 9 part 1
Module: Text
Filename: Text.cpp
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define  _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "Text.h"
using namespace std;

namespace sdds {

	// private member functions

	void Text::setEmpty() {
		delete [] m_content;
		m_content = nullptr;
	}

	// protected member functions

	const char& Text::operator[](int index) const {
		return m_content[index];
	}


	// public member functions

	void Text::allocateAndCopy(const char* content) {
		delete [] m_content;	// release current memory storage if any

		m_content =  new (nothrow) char[strlen(content)+1];	// allocate new memory storage

		if (m_content!= nullptr) { 
			strcpy(m_content, content);	// copy data to newly allocated memory location
		}
	}

	Text::Text() {
		m_content = nullptr;
	}

	Text::~Text() {
		setEmpty();
	}

	Text::operator bool() const {
		return (m_content != nullptr) ? true : false;
	}

	Text::Text(const Text& textObject) {
		*this = textObject;
	}

	Text& Text::operator=(const Text& textObject) {
		if (this != &textObject && textObject) {	// check that addresses are not the same and textObject is valid
			allocateAndCopy(textObject.m_content);
		} else {
			setEmpty();
		}
		return *this;
	}

	ostream& Text::write(ostream& ostr) const {
		if (*this) {	// check if current object is valid
			ostr << m_content;
		} // do nothing if current object is not valid
		return ostr;
	}

	istream& Text::read(istream& istr) {
		int fileSize = 0;

		setEmpty();		// deallocates the content in this object

		fileSize = getFileLength(istr);	// get size of stream

		m_content =  new (nothrow) char[fileSize+1];	// allocate new memory storage

		istr.get(m_content, (fileSize+1), '\0');	// store stream into m_content

		if (!istr.fail()) istr.clear();	// clear the istream

		return istr;
	}

	// helper functions

	ostream& operator<<(ostream& ostr, const Text& textObject) {
		return textObject.write(ostr);
	}

	istream& operator>>(istream& istr, Text& textObject) {
		return textObject.read(istr);
	}

	int getFileLength(std::istream& is)  {
		int len{};
		if (is) {
			// save the current read position
			std::streampos cur = is.tellg();
			// go to the end
			is.seekg(0, ios::end);
			// let what is the positions (end position = size)
			len = is.tellg();
			// now go back to where you were.
			is.seekg(cur);
		}
		return len;
	}
}