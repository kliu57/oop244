/* ------------------------------------------------------
Workshop 7 part 1
Module: Pack
Filecontainer: Pack.h
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_PACK_H
#define SDDS_PACK_H

#include "Container.h"

namespace sdds {
    class Pack : public Container { // start of Derived Class Definition 
        int m_unitSize;
    public:
        // constructor
        Pack(const char content[], int size, int unitSize = 330, int numUnits = 0);

        // Shadows the operator+= of the Base class
        // Receives a number to add units to the pack and returns the number of units successfully added
        int operator+=(int value);

        // Shadows the operator-= of the Base class
        // Receives a number to remove units from the pack and returns the number of units successfully removed
        int operator-=(int value);

        // Returns the unit size attribute
        int unit() const;

        // Returns the content volume of the Base class divided by the unit size
        int noOfUnits() const;

        // Return the capacity of the base class divided by the unit size
        int size() const;

        // Overloads the clear function of the Base class
        // If the unit size is greater than zero it will call the clear of the base class passing the product of pack size and the unit size and the content description
        // Then it will set the unit size attribute to the unit size argument
        void clear(const int packSize, int unitSize, const char content[]);

        // Shadows the print of the Base class
        // Print the pack to screen
        std::ostream& print(std::ostream& ostr) const;

        // Shadows the read of the Base class
        // Reads from user input
        std::istream& read(std::istream& istr);
    };      // end of Derived Class definition

    // insertion operator overload
    // returns the print method of the pack argument
    std::ostream& operator<<(std::ostream& ostr, const Pack& packObject);

    // extraction operator overload
    // returns the read method of the pack argument
    std::istream& operator>>(std::istream& istr, Pack& packObject);
}
#endif // !SDDS_PACK_H