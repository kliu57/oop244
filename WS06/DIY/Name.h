/* ------------------------------------------------------
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
Date    Sun Mar 6 2022

Workshop 6 part 2
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

        // Returns true if cstring contains one or more spaces
        bool containsSpaces(const char* cstring) const;

        // Returns true if name consists of one or more nonspace characters
        bool validName(const char* name) const;

        // Sets the HeathCard object to a recognizable empty (invalid) state
        void setEmpty();

        // Free memory and newly allocate memory for first name, copy cstring pointed by argument to newly allocated memory location
        void allocateAndCopyFName(const char* fname);

        // Free memory and newly allocate memory for last name, copy cstring pointed by argument to newly allocated memory location
        void allocateAndCopyLName(const char* lname);

        // Free memory and newly allocate memory for middle name, copy cstring pointed by argument to newly allocated memory location
        void allocateAndCopyMName(const char* mname);

        // Prints first name, followed by middle name (if existing and abbreviated or full according to flag), followed by last name (if existing)
        std::ostream& printName(std::ostream& ostr) const;

        // sets first, middle, and last name member variables
        void set(const char* fname, const char* lname = nullptr, const char* mname = nullptr);
    public:
        // constructors - if any argument given is not a valid name then sets the object to a safe empty state
        Name();
        Name(const char* fname);
        Name(const char* fname, const char* lname);
        Name(const char* fname, const char* lname, const char* mname);

        // destructor - clears allocated memory
        ~Name();

        // copy constructor - If the argument object is valid it will set the values of the current object to those of the incoming argument
        Name(const Name& name);

        // Set the values of the current object to those of the incoming argument only if it this is not a "self-copy"
        Name& operator=(const Name& nameObject);

        // If the first name is null, it will set the first name. Otherwise, if the middle name is null it will set the middle name, or else, if the last name is null, it will set the last name
        // If the name has all the three parts, the operation fails and sets the object into an invalid empty state
        // If there are spaces in the Cstring the operation fails. The Name object is then set to an invalid state
        // If the string is null or empty the operation is aborted and the object will not change
        Name& operator+=(const char* name);

        // Boolean type conversion operator - Returns true if m_fname is not nullptr, else it will return false
        operator bool() const;

        // Sets member variable representing display of abbreviated or full middle name to true or false
        void setShort(bool isShort);

        // Prints name to screen or to file
        std::ostream& print(std::ostream& ostr, bool toFile = true) const;

        // Reads name from user input or from file
        std::istream& read(std::istream& istr);
    };

    // Insertion operator overload
    // If argument object is valid it will print it using the print function on the screen and not on File. Otherwise, it will print "Bad Name"
    // Returns the ostr reference
    std::ostream& operator<<(std::ostream& ostr, const Name& nameObject);

    // Extraction operator overload
    // Returns the read method of the argument object
    std::istream& operator>>(std::istream& istr, Name& nameObject);
}
#endif // !SDDS_NAME_H