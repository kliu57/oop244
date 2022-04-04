/* ------------------------------------------------------
Workshop 9 part 1
Module: Text
Filename: Text.h
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_TEXT_H
#define SDDS_TEXT_H

#include <iostream>

namespace sdds {
    class Text {
        char* m_content = nullptr;    // holds content of the text file dynamically

        // Sets the Text object to a recognizable empty (invalid) state by releasing memory and setting m_content to nullptr
        void setEmpty();

    protected:
        // This index operator provides read-only access to the content of the text for the derived classes of Text.
        // The behaviour of the operator is not defined if the index goes out of bounds or if the content is null.
        const char& operator[](int index) const;

    public:
        // Free the memory pointed by m_content
        // Allocate enough memory to store name Cstring
        // Copy the Cstring pointed by content into the newly allocated memory pointed by m_content
        void allocateAndCopy(const char* content);

        // Returns m_content
        const char* getContent() const;

        // Sets m_content
        void setContent(const char* content);

        // constructor
        Text();

        // destructor
        // deletes the memory pointed by m_content
        ~Text();

        // Boolean type conversion operator
        // Returns true if m_content is not nullptr, else it will return false
        operator bool() const;

        // copy constructor
        // if the Text object is valid it will set the values of the current object to those of the incoming argument (Text using assignment to *this)
        Text(const Text& textObject);

        // Copy Assignment operator overload
        // First, it will make sure that this is not a "self-copy" by comparing the address of the current object and the address of the incoming argument
        // If it is not a self copy this function works exactly like the copy constructor
        // If it is a self copy don't perform any action At the end return the reference of the current object
        Text& operator=(const Text& textObject);

        // Receives an ostream reference and returns it at the end of the function.
        // This virtual function will insert the content of the Text class into the ostream if m_content is not null.
        // Also, this function does not change the content of a file.
        virtual std::ostream& write(std::ostream& ostr) const;

        // Receives an istream reference and returns it at the end.
        // - deallocates the content
        // - allocates memory to the size of the file on the disk + 1 (for the null byte).
        // - reads the file into the allocated memory (character by character to the end)
        // - if any data is read, it will clear() the state of the istream object, otherwise, it will leave it as is.
        std::istream& read(std::istream& istr);
    };

    // insertion operator overload
    // returns the print method of the text object argument
    std::ostream& operator<<(std::ostream& ostr, const Text& textObject);

    // extraction operator overload
    // returns the read method of the text object argument
    std::istream& operator>>(std::istream& istr, Text& textObject);

    int getFileLength(std::istream& is);
}
#endif // !SDDS_TEXT_H