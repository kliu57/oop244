/* ------------------------------------------------------
Workshop 9 part 1
Module: HtmlText
Filename: HtmlText.h
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_HTMLTEXT_H
#define SDDS_HTMLTEXT_H

#include "Text.h"

namespace sdds {
    class HtmlText : public Text {
        char* m_title = nullptr;      // title of the Html conversion dynamically;

        // Sets the Text object to a recognizable empty (invalid) state by releasing memory and setting m_content to nullptr
        void setEmpty();

        // Free the memory pointed by m_content
        // Allocate enough memory to store name Cstring
        // Copy the Cstring pointed by content into the newly allocated memory pointed by m_content
        void allocateAndCopy(const char* content);

    public:
        // constructor
        HtmlText(const char* title = nullptr);

        // destructor
        // deletes the memory pointed by m_content
        ~HtmlText();

        // copy constructor
        // if the Text object is valid it will set the values of the current object to those of the incoming argument (Text using assignment to *this)
        HtmlText(const HtmlText& textObject);

        // Copy Assignment operator overload
        // First, it will make sure that this is not a "self-copy" by comparing the address of the current object and the address of the incoming argument
        // If it is not a self copy this function works exactly like the copy constructor
        // If it is a self copy don't perform any action At the end return the reference of the current object
        HtmlText& operator=(const HtmlText& textObject);

        // Receives an ostream reference and returns it at the end of the function.
        // This virtual function will insert the content of the Text class into the ostream if m_content is not null.
        // Also, this function does not change the content of a file.
        std::ostream& write(std::ostream& ostr) const;
    };
}
#endif // !SDDS_HTMLTEXT_H