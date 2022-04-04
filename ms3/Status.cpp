/* ------------------------------------------------------
Final Project Milestone 3
Module: Status
Filestatus: Status.cpp
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define  _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "Status.h"
#include "Utils.h"
using namespace std;
namespace sdds {
	// public member functions

	Status::Status(const char* desc) {
		ut.alocpy(m_desc, desc);	// safely alloc dynamic memory - copy desc of argument object to m_desc
		m_code = 0;
	}

	Status::~Status() {
		delete [] m_desc;
	}

	// copy constructor
	Status::Status(const Status& statusObject) {
		*this = statusObject;
	}

	Status& Status::operator=(const Status& statusObject) {
		if (this != &statusObject) {	// check that addresses are not the same
			ut.alocpy(m_desc, statusObject.m_desc);		// safely alloc dynamic memory - copy desc of argument object to m_desc
			m_code = statusObject.m_code;				// shallow copy of code of argument object to m_code
		} else {
			clear();
		}
		return *this;
	}

	Status& Status::operator=(const char* desc) {
		if (desc != nullptr) {
			if (&m_desc != &desc) {	// check that addresses are not the same and arg object is valid
				ut.alocpy(m_desc, desc);		// safely alloc dynamic memory - copy desc of argument object to m_desc
			} else {
				clear();
			}
		} else {
			clear();
		}
		return *this;
	}

	Status& Status::operator=(int code) {
		m_code = code;
		return *this;
	}

	Status::operator const char*() const {
		return m_desc;
	}

	Status::operator int() const {
		return m_code;
	}

	Status::operator bool() const {
		return (m_desc == nullptr) ? true : false;
	}

	Status& Status::clear() {
		delete [] m_desc;
		m_desc = nullptr;
		m_code = 0;
		return *this;
	}

	ostream& Status::print(ostream& ostr) const {
		if (!*this) {	// only print if current object is invalid
			if (m_code != 0) {	// only print error code if not zero
				ostr << "ERR#" << m_code << ": ";
			}
			ostr << m_desc;
		}
		return ostr;
	}

	// helper functions

	ostream& operator<<(ostream& ostr, const Status& statusObject) {
		return statusObject.print(ostr);
	}
}
