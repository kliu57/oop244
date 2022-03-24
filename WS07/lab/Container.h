/* ------------------------------------------------------
Workshop 7 part 1
Module: Container
Filecontainer: Container.h
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_CONTAINER_H
#define SDDS_CONTAINER_H

#include <iostream>
#include <istream>

namespace sdds {
    class Container {
        char m_content[51];
        int m_capacity;
        int m_contentVolume;
    protected:
        // Sets the Container object to a recognizable empty (invalid) state
        void setEmpty();

        // Returns the capacity
        int capacity() const;

        // Returns the content volume
        int volume() const;
    public:
        // constructor
        Container(const char content[], int capacity, int contentVolume = 0);

        // Adds to the content volume and returns the amount added
        int operator+=(int value);

        // Deduct from the content volume and returns the amount deducted
        int operator-=(int value);

        // Boolean type conversion operator
        // Returns true if Container is in a valid state, false otherwise
        operator bool() const;

        // If args are valid then sets the attributes, making the container valid
        void clear(int capacity, const char content[]);

        // Prints the container to screen
        std::ostream& print(std::ostream& ostr) const;

        // Reads from user input
        std::istream& read(std::istream& istr);
    };

    // insertion operator overload
    // returns the print method of the container argument
    std::ostream& operator<<(std::ostream& ostr, const Container& containerObject);

    // extraction operator overload
    // returns the read method of the container argument
    std::istream& operator>>(std::istream& istr, Container& containerObject);
}
#endif // !SDDS_CONTAINER_H