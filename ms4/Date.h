/* ------------------------------------------------------
Final Project Milestone 4
Module: Date
Filename: Date.h
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_DATE_H
#define SDDS_DATE_H
#include <iostream>
#include <istream>
#include "Status.h"
namespace sdds {
    const int MAX_YEAR_VALUE = 2030;
    class Date {
        int m_year;
        int m_month;
        int m_day;
        Status m_state;
        bool m_isFormatted;

        // Validates year, month, day of current object and sets state accordingly
        bool validate();

        // Return unique integer value tied to date
        int uniqueInt() const;
    public:
        // constructors
        Date();
        Date(int year, int month, int day);
        Date(int sixDigitNum);

        // Returns true if date objects have the same date
        bool operator==(const Date& dateObject) const;

        // Returns true if date objects do not have the same date
        bool operator!=(const Date& dateObject) const;

        // Returns true if current date object's date is prior to argument date object's date
        bool operator<(const Date& dateObject) const;

        // Returns true if current date object's date is later than argument date object's date
        bool operator>(const Date& dateObject) const;

        // Returns true if current date object's date is equal or prior to argument date object's date
        bool operator<=(const Date& dateObject) const;

        // Returns true if current date object's date is equal or later than argument date object's date
        bool operator>=(const Date& dateObject) const;

        // Boolean type conversion operator - Returns state of date object
        operator bool() const;

        // Returns a constant reference to the state
        Status& state() const;

        // Sets m_isFormatted to argument
        // Returns reference of the current object
        Date& formatted(bool isFormatted);

        // Prints the date object
        std::ostream& write(std::ostream& ostr) const;

        // Reads from istream object and extracts date value
        std::istream& read(std::istream& istr);
    };

    // Insertion operator overload
    // Prints status of argument object
    // Returns the ostr reference
    std::ostream& operator<<(std::ostream& ostr, const Date& dateObject);

    // Extraction operator overload
    // Returns the read method of the argument object
    std::istream& operator>>(std::istream& istr, Date& dateObject);
}
#endif // !SDDS_DATE_H