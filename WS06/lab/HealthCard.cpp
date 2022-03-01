#define  _CRT_SECURE_NO_WARNINGS

#include "HealthCard.h"
using namespace std;
namespace sdds {

	// private member functions

	bool HealthCard::validID(const char* name, long long number, const char vCode[], const char sNumber[]) const {
		bool nameValid = false;
		if (name != nullptr) {
			if (name[0] != '\0') {
				nameValid = true;
			}
		}

		bool numValid = (number > 999999999 && number <= 9999999999) ? true : false;

		bool verValid = false;
		if (vCode != nullptr) {
			if (strlen(vCode) == 2) {
				verValid = true;
			}
		}

		bool scValid = false;
		if (sNumber != nullptr) {
			if (strlen(sNumber) == 9) {
				scValid = true;
			}
		}

		// return true if all arguments pass validation
		return (nameValid && numValid && verValid && scValid) ? true : false;
	}

	void HealthCard::setEmpty() {
		m_name = nullptr;
		m_number = 0;
		m_vCode[0] = '\0';
		m_sNumber[0] = '\0';
	}

	void HealthCard::allocateAndCopy(const char* name) {
		delete [] m_name;					// delete previously allocated memory for name, if any
		m_name = new char[strlen(name)+1];	// newly allocate memory for name
		strcpy(m_name, name);				// copy string to new memory location
	}

	void HealthCard::extractChar(istream& istr, char ch) const {
		char next;
		next = istr.peek();

		if (next == ch) { // checking if the next character in keyboard is same as ch
			istr.ignore();					// throw away this character
		} else{
			cin.ignore(1000, ch);			// throw away everything after or until ch
			istr.setstate(ios::failbit);	// Set the istream into a fail state
		}
	}

	ostream& HealthCard::printIDInfo(ostream& ostr) const {
		ostr << m_number << '-' << m_vCode << ", " << m_sNumber;
		return ostr;
	}

	void HealthCard::set(const char* name, long long number, const char vCode[], const char sNumber[]) {
		if (validID(name, number, vCode, sNumber)) {
			allocateAndCopy(name);		// set name
			m_number = number;			// set number
			strcpy(m_vCode, vCode);		// set version code
			strcpy(m_sNumber, sNumber);	// set stock control number
		} else {
			setEmpty();
		}
	}

	// public member functions

	HealthCard::HealthCard(const char* name, long long number, const char vCode[], const char sNumber[]) {
		set(name, number, vCode, sNumber);
	}

	HealthCard::~HealthCard() {
		delete [] m_name;	// delete allocated memory for name
		m_name = nullptr;
	}

	HealthCard::HealthCard(const HealthCard& hc) {
		if (hc) {
			allocateAndCopy(hc.m_name);			// set name
			m_number = hc.m_number;				// set number
			strcpy(m_vCode, hc.m_vCode);		// set version code
			strcpy(m_sNumber, hc.m_sNumber);	// set stock control number
		}
	}

	HealthCard& HealthCard::operator=(const HealthCard& hc) {
		if (this != &hc) {	// compare address of current object and argument object
			if (hc) {
				allocateAndCopy(hc.m_name);			// set name
				m_number = hc.m_number;				// set number
				strcpy(m_vCode, hc.m_vCode);		// set version code
				strcpy(m_sNumber, hc.m_sNumber);	// set stock control number
			}
		}
		return *this;
	}

	HealthCard::operator bool() const {
		return (m_name != nullptr) ? true : false;
	}

	ostream& HealthCard::print(ostream& ostr, bool toFile) const {
		if (*this) {	// check if current object is valid
			if (toFile) {
				// prints data in comma-separated format
				ostr << m_name << ',';
				printIDInfo(ostr);
			} else {
				streamsize oldPrecision = ostr.precision();	// save precision
				ostr.setf(ios::left);	// set left align
				ostr.width(50);
				ostr.fill('.');		// set fill character to dots

				ostr << m_name;

				ostr.fill(' ');		// set fill character back
				ostr.unsetf(ios::left);	// unset left align
				ostr.precision(oldPrecision);	// change precision back

				printIDInfo(ostr);
			}
		}
		return ostr;
	}

	istream& HealthCard::read(istream& istr) {
		char r_name[MaxNameLength+1];
		long long r_num = 0;
		char r_vCode[MaxVerLength+1];
		char r_sNumber[MaxSCLength+1];

		istr.get(r_name, MaxNameLength+1, ',');		// read the name up to MaxNameLength or a comma and store
		extractChar(istr, ',');						// read and discard comma
		istr >> r_num;								// read number
		extractChar(istr, '-');						// read and discard dash
		istr.get(r_vCode, MaxVerLength+1, ',');		// read the version code up to MaxVerLength or a comma and store
		extractChar(istr, ',');						// read and discard comma
		istr.getline(r_sNumber, MaxSCLength+1, '\n');	// read the version code up to MaxSCLength or newline and store

		if (!istr.fail()) {		// checks if istr is in a failed state
			set(r_name, r_num, r_vCode, r_sNumber);	// set object to read values

			istr.clear();	
		}
		else {
			istr.clear();				// clears state to allow further extraction
			istr.ignore(2000, '\n');	// clears the input buffer
		}



		return istr;
	}

	// helper functions

	ostream& operator<<(ostream& ostr, const HealthCard& hc) {
		if (hc) {
			hc.print(ostr, false);
		} else {
			ostr << "Invalid Health Card Record";
		}
		return ostr;
	}

	istream& operator>>(istream& istr, HealthCard& hc) {
		return hc.read(istr);
	}
}
