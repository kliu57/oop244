/* ------------------------------------------------------
Workshop 9 part 1
Module: HtmlText
Filename: HtmlText.cpp
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define  _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "HtmlText.h"
using namespace std;

namespace sdds {

	// private member functions

	void HtmlText::setEmpty() {
		delete [] m_title;
		m_title = nullptr;
	}

	void HtmlText::allocateAndCopy(const char* title) {
		delete [] m_title;	// release current memory storage if any

		if (title != nullptr) {
			m_title =  new (nothrow) char[strlen(title)+1];	// allocate new memory storage

			if (m_title!= nullptr) { 
				strcpy(m_title, title);	// copy data to newly allocated memory location
			}
		} else {
			m_title = nullptr;
		}
	}

	// public member functions

	HtmlText::HtmlText(const char* title) : Text() {
		m_title = nullptr;

		if (title != nullptr) {
			HtmlText::allocateAndCopy(title);
		}
	}

	HtmlText::~HtmlText() {
		setEmpty();
	}

	HtmlText::HtmlText(const HtmlText& htObject) : Text() {
		HtmlText::allocateAndCopy(htObject.m_title);	// copies title even if null

		// set text object content to argument
		Text::setContent(htObject.getContent());
	}

	HtmlText& HtmlText::operator=(const HtmlText& htObject) {
		if (this != &htObject) {	// check that addresses are not the same
			HtmlText::allocateAndCopy(htObject.m_title);

			// set text object content to argument
			Text::setContent(htObject.getContent());
		} else {
			setEmpty();
		}
		return *this;
	}

	ostream& HtmlText::write(ostream& ostr) const {
		char ch = 0;
		char lastCh = 0;

		ostr << "<html><head><title>" << (m_title != nullptr ? m_title : "No Title") << "</title></head>\n<body>\n";

		if (m_title != nullptr) {
			ostr << "<h1>" << m_title << "</h1>" << endl;
		}
		
		// go character by character and either replace and print or print
		for (int i = 0; i < (int)strlen(Text::getContent()); i++) {
			ch = Text::operator[](i);

			// check for things to be replaced before print
			switch(ch) {
			case '<':
				ostr << "&lt;";
				break;
			case '>':
				ostr << "&gt;";
				break;
			case '\n':
				ostr << "<br />\n";
				break;
			case ' ':
				if (lastCh == ' ') {
					ostr << "&nbsp;";	// if last char was a space then replace it
				} else {
					ostr << ch;
				}
				break;
			default:
				ostr << ch;	// no change
			}

			lastCh = ch;
		}

		ostr << "</body>\n</html>";

		return ostr;
	}
}