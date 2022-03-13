/* ------------------------------------------------------
Final Project Milestone 1
Module: Status
Filestatus: Status.h
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H
#include <iostream>
namespace sdds {
    class Status {
        char* m_desc{};
        int m_code;
    public:
        // constructor - initialize object m_desc to argument if given and m_code to 0
        Status(const char* desc = nullptr);

        // destructor - clears allocated memory
        ~Status();

        // copy constructor - If the argument object is valid it will set the values of the current object to those of the incoming argument
        Status(const Status& status);

        // Set the values of the current object to those of the incoming argument only if it this is not a "self-copy"
        Status& operator=(const Status& statusObject);

        // Sets m_desc to right operand
        Status& operator=(const char* desc);

        // Sets m_code to right operand
        Status& operator=(int code);

        // Constant character pointer type conversion operator - Returns m_desc
        operator const char*() const;

        // Integer type conversion operator - Returns m_code
        operator int() const;

        // Boolean type conversion operator - Returns true if m_desc is not nullptr, else it will return false
        operator bool() const;

        // Sets the object to a recognizable empty (invalid) state
        Status& clear();

        // prints status of object if object invalid
        std::ostream& print(std::ostream& ostr) const;
    };

    // Insertion operator overload
    // Prints status of argument object
    // Returns the ostr reference
    std::ostream& operator<<(std::ostream& ostr, const Status& statusObject);
}
#endif // !SDDS_STATUS_H