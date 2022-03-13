/* ------------------------------------------------------
Final Project Milestone 1
Module: Date
Filename: Date.cpp
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define  _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iomanip>
#include "Date.h"
#include "Utils.h"
using namespace std;
namespace sdds {
	// private member functions

	bool Date::validate() {
		bool isValid = false;
		int currentYear = 0;
		int currentMonth = 0;
		int currentDay = 0;
		Utils ut;
		ut.testMode(true);
		ut.getSystemDate(&currentYear, &currentMonth, &currentDay);	// get current date
		if (m_year >= currentYear && m_year <= MAX_YEAR_VALUE) {	// check if year is valid
			if (m_month >= 1 && m_month <= 12) {	// check if month is valid
				if (m_day >= 1 && m_day <= ut.daysOfMon(m_month, m_year)) {	// check if day is valid
					// Everything is valid, clear state
					m_state.clear();
					isValid = true;
				} else {
					// set state
					m_state = "Invalid day in date";
					m_state = 3;
				}
			} else {
				// set state
				m_state = "Invalid month in date";
				m_state = 2;
			}
		} else {
			// set state
			m_state = "Invalid year in date";
			m_state = 1;
		}
		return isValid;
	}

	int Date::uniqueInt() const {
		return m_year * 372 + m_month * 31 + m_day;
	}

	// public member functions

	Date::Date() {
		Utils ut;
		ut.testMode(true);
		ut.getSystemDate(&m_year, &m_month, &m_day);	// set member variables to current date

		cout << "a new date obj init to: " << m_day << endl;
		m_isFormatted = true;
	}

	Date::Date(int year, int month, int day) {
		m_year = year;
		m_month = month;
		m_day = day;
		validate();	// validates date and sets state accordingly
		m_isFormatted = true;
	}

	bool Date::operator==(const Date& dateObject) const {
		bool isEqual = false;
		if (m_year == dateObject.m_year &&
			m_month == dateObject.m_month &&
			m_day == dateObject.m_day
			) {
			isEqual = true;
		}
		return isEqual;
	}

	bool Date::operator!=(const Date& dateObject) const {
		return !(*this == dateObject);
	}

	bool Date::operator<(const Date& dateObject) const {
		// convert both date objects to integers and compare
		return uniqueInt() < dateObject.uniqueInt();
	}

	bool Date::operator>(const Date& dateObject) const {
		// convert both date objects to integers and compare
		return uniqueInt() > dateObject.uniqueInt();
	}

	bool Date::operator<=(const Date& dateObject) const {
		// convert both date objects to integers and compare
		return uniqueInt() <= dateObject.uniqueInt();
	}

	bool Date::operator>=(const Date& dateObject) const {
		// convert both date objects to integers and compare
		return uniqueInt() >= dateObject.uniqueInt();
	}

	Date::operator bool() const {
		return (bool)m_state;
	}

	Status& Date::state() const {
		return (Status&)m_state;
	}

	Date& Date::formatted(bool isFormatted) {
		m_isFormatted = isFormatted;
		return *this;
	}

	ostream& Date::write(ostream& ostr) const {
		if (m_isFormatted) {
			ostr << m_year;		// print year
			ostr << "/";
			ostr << right << setfill('0') << setw(2) << m_month;	// print month
			ostr << "/";
			ostr << setw(2) << m_day;	// print day
		} else {
			ostr << m_year % 100;		// print last two digits of year
			ostr << right << setfill('0') << setw(2) << m_month;	// print month
			ostr << setw(2) << m_day;	// print day
		}
		ostr.fill(' ');				// change fill back to default
		ostr.unsetf(ios::right);	// change format back to default
		return ostr;
	}

	istream& Date::read(istream& istr) {
		int num = 0;
		int currentYear = 0;
		int currentMonth = 0;
		int currentDay = 0;
		Utils ut;
		ut.testMode(true);
		cin >> num;    // read from user input, input stream object will be set to fail state if user input is not an integer
		if (!cin.fail()) {	// check if an integer was read successfully
			// an integer was read
			ut.getSystemDate(&currentYear, &currentMonth, &currentDay);	// get current date

			if (num >= 1000 && num <= 9999) {	// check if integer is 4 digits
				m_year = currentYear;	// set to current year
				m_month = num / 100;	// get first 2 digits as the month
				m_day = num % 100;		// get last 2 digits as the day
			} else if (num >= 100000 && num <= 999999) {	// check if integer is 6 digits
				m_year = (currentYear - currentYear % 100) + (num / 10000);		// get first 2 digits as the year and combine with first two digits of current year
				m_month = num / 100 % 100;	// get middle 2 digits as the month
				m_day = num % 100;			// get last 2 digits as the day
			} else {
				m_year = currentYear;
				m_month = 0;
				m_day = 0;
			}

			if (!validate()) {	// validate date
				istr.setstate(ios::badbit);
			}
		} else {
			// an integer was not read
			m_year = 0;
			m_month = 0;
			m_day = 0;
			m_state = "Invalid date value";
			m_state = 0;
		}
		return istr;
	}

	// helper functions

	ostream& operator<<(ostream& ostr, const Date& dateObject) {
		return dateObject.write(ostr);
	}

	istream& operator>>(istream& istr, Date& dateObject) {
		return dateObject.read(istr);
	}
}