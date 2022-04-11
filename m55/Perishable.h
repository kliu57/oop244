/* ------------------------------------------------------
Final Project Milestone 5
Module: Perishable
Filestatus: Perishable.h
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H
#include "Item.h"
#include "Date.h"
namespace sdds {
    // An Perishable is a concrete Perishable to keep track of the quantity and on-hand-quantity perishables to be prepared for shipping
    class Perishable : public Item {
        Date m_expiryDate;
        char* m_instr{};

        // set object to invalid state
        void setEmpty();

    public:
        // constructor
        // sets all the attributes to zero, nullptr and false
        Perishable();

        // destructor
        ~Perishable();

        // copy constructor
        // if the Perishable object is valid it will set the values of the current object to those of the incoming argument (Perishable using assignment to *this)
        Perishable(const Perishable& perishableObject);

        // Copy Assignment operator overload
        // First, it will make sure that this is not a "self-copy" by comparing the address of the current object and the address of the incoming argument
        // If it is not a self copy this function works exactly like the copy constructor
        // If it is a self copy set to empty state At the end return the reference of the current object
        Perishable& operator=(const Perishable& perishableObject);

        // returns the expiry date object
        Date expiry() const;

        // saves the Perishable into a file
        // In the end, the reference of the ofstream is returned
        std::ofstream& save(std::ofstream& ofstr) const;

        // loads an Perishable from a file
        // Reads the item, followed by the instructions and the expiry date
        // If ifstream is in a bad state after the read the state of the perishable will be set to "Input file stream read (perishable) failed!"
        // In the end, the reference of ifstream is returned
        std::ifstream& load(std::ifstream& ifstr);

        // displays the Perishable on the screen
        std::ostream& display(std::ostream& ostr) const;

        // Reads the SKU from the screen with the prompt "SKU: ". It makes sure the SKU number begins with digits 1 to 3 and it is 5 digits long.
        int readSku(std::istream& istr);

        // reads the Item from the console
        std::istream& read(std::istream& istr);
    };
}
#endif // !SDDS_PERISHABLE_H