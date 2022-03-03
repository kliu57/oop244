/* ------------------------------------------------------
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
Date    Tue Mar 01 2022

Workshop 6 part 1
Module: Name
Desc:   Module for Name object and functions
Filename: Name.h
-----------------------------------------------------------*/
#ifndef SDDS_NAME_H
#define SDDS_NAME_H

#include <iostream>
#include <istream>

namespace sdds {
    const int MAX_INPUT_LENGTH = 55;
    class Name {
        char* m_fname{};
        char* m_mname{};
        char* m_lname{};
        bool m_isShort;

        // Returns true if name consists of one or more nonspace characters
        bool validName(const char* name) const;

        // Sets the HeathCard object to a recognizable empty (invalid) state by setting m_fname to nullptr
        void setEmpty();

        // Free the memory pointed by m_fname
        // Allocate enough memory to store name Cstring
        // Copy the Cstring pointed by name into the newly allocated memory pointed by m_fname
        void allocateAndCopyFName(const char* fname);
        void allocateAndCopyLName(const char* lname);
        void allocateAndCopyMName(const char* mname);

        // "peek()" and see if the next character in the keyboard buffer is the same as the ch argument
        // If it is the same, Remove it from the keyboard and throw it away! (i.e. istr.ignore())
        // If not:
        // Ignore all the remaining characters (up to 1000 characters) or the value of ch (use istr.ignore(int n,char c))
        // Set the istream into a fail state (use istr.setstate(iso::failbit))
        void extractChar(std::istream& istr, char ch) const;
        void extractChar(std::istream& istr, char chA, char chB) const;

        // Inserts the three parts related to the main card number, version code and stock number of the health card information into the istr object in the following format:
        // 1234567890-AB, XY7652341
        // and then returns the istr object reference ostream& printName(ostream& ostr)const;
        std::ostream& printName(std::ostream& ostr) const;

        // Validates the arguments, reallocates memory for the name and sets the object attributes to their corresponding values.
        // If the name and the three parts are valid (see Validation) call the private function to validate
        // Calls the reallocateAndCopy function to set the name
        // Sets the three parts to their values (m_number, m_vCode, m_sNumber)
        // If not, it deletes the memory pointed by m_fname and sets the object to a safe empty state (setEmpty())
        void set(const char* fname, const char* lname = nullptr, const char* mname = nullptr);
    public:
        // constructors
        Name();
        Name(const char* fname);
        Name(const char* fname, const char* lname);
        Name(const char* fname, const char* lname, const char* mname);

        // destructor
        // deletes the memory pointed by m_fname
        ~Name();

        // copy constructor
        // if the hc object is valid it will set the values of the current object to those of the incoming argument (hc using assignment to *this)
        Name(const Name& name);

        Name& operator+=(const char* name);

        // Boolean type conversion operator
        // Returns true if m_fname is not nullptr, else it will return false
        operator bool() const;


        void setShort(bool isShort);

        /*
        If the current object is in a valid state it inserts the values of the card information in two different formats based on the value of the toFile argument :
        if toFile is true, prints the data in a comma-separated format:
        prints the name
        print comma
        print the health card ID information using the private function printName
        if toFile is false prints the data in the following format:
        In 50 characters, left-justified and padded with dots ('.'): prints the name
        print the health card ID information using the private function printName
        At the end, it returns the ostr reference
        */
        std::ostream& print(std::ostream& ostr, bool toFile = true) const;

        // Reads the Contact information in following format:
        // Example: Luke Skywalker,1231231234-XL,AF1234567
        std::istream& read(std::istream& istr);
    };

    // insertion operator overload
    // if hc is valid it will print it using the print function on the screen and not on File, (i.e. onFile is false). Otherwise, it will print "Invalid Card Number".
    // In the end, it will return the ostr reference.
    std::ostream& operator<<(std::ostream& ostr, const Name& hc);

    // extraction operator overload
    // returns the read method of the hc argument.
    std::istream& operator>>(std::istream& istr, Name& hc);
}
#endif // !SDDS_NAME_H