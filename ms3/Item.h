/* ------------------------------------------------------
Final Project Milestone 3
Module: Item
Filestatus: Item.h
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H
#include "iProduct.h"
#include "Status.h"
namespace sdds {
    // An Item is a concrete Item to keep track of the quantity and on-hand-quantity items to be prepared for shipping
    class Item : public iProduct {
        char* m_desc;
        int m_qty;
        int m_qtyNeeded;
        double m_price;
        bool m_isLinear;

        // set object to invalid state
        void setEmpty();

    protected:
        int m_sku;
        Status m_state;
        // returns the linear flag of the Item
        bool linear();
    public:
        // constructor
        // sets all the attributes to zero, nullptr and false
        Item();

        // destructor
        ~Item();

        // copy constructor
        // if the Item object is valid it will set the values of the current object to those of the incoming argument (Item using assignment to *this)
        Item(const Item& itemObject);

        // Copy Assignment operator overload
        // First, it will make sure that this is not a "self-copy" by comparing the address of the current object and the address of the incoming argument
        // If it is not a self copy this function works exactly like the copy constructor
        // If it is a self copy set to empty state At the end return the reference of the current object
        Item& operator=(const Item& itemObject);

        // returns the number of products needed
        int qtyNeeded() const;

        // retuns the quantity on hand
        int qty() const;

        // Double type conversion operator
        // returns the price of the produce
        operator double() const;

        // Boolean type conversion operator
        // returns if the Item is in a good state
        operator bool() const;

        // does not accept any argument and sets the state of the Item object back to good, by resetting the state attribute
        void clear();

        // to reduce the quantity on hand
        int operator-=(int qty);

        // to increase the quantity on hand
        int operator+=(int qty);

        // sets the linear flag
        void linear(bool isLinear);

        // return true if the sku is a match to the Item's sku
        // the integer comparison returns true if the SKU attribute matches the received value
        bool operator==(int sku) const;

        // retrns true if the description is found in the iProduct's description
        // the constant character pointer comparison searches in the description of the Item for the appearance of the received Cstring.
        // If a match was found it returns true.
        // If any of the descriptions (The Items or the received value) are null or the match is not found, it will return false.
        bool operator==(const char* description) const;

        // saves the Item into a file
        // If the state of the Item is good, it will write SKU, description, on-hand quantity, needed quantity and price in tab-separated format.
        // note that the price should be written with 2 digits after the decimal point.
        // No newline is added.
        // If the state is not good, it will do nothing.
        // In the end, the reference of the ofstream is returned.
        std::ofstream& save(std::ofstream& ofstr) const;

        // loads an Item from a file
        // After deallocating the description:
        // The tab-separated SKU, description, on-hand quantity, needed quantity and price are read into their corresponding attributes and then a single character is discarded from the file.
        // If ifstream is in a bad state after the read the state of the item will be set to "Input file stream read failed!"
        // Note that the description is dynamically allocated
        // In the end, the reference of ifstream is returned.
        std::ifstream& load(std::ifstream& ifstr);

        // displays the Item on the screen
        std::ostream& display(std::ostream& ostr) const;

        // to read the Stock-Keeping Unit from console before
        // main data entry
        // Reads the SKU from the screen with the prompt "SKU: ". It makes sure the SKU number begins with digits 4 to 9 and it is 5 digits long.
        int readSku(std::istream& istr);

        // reads the Item from the console
        std::istream& read(std::istream& istr);
    };
}
#endif // !SDDS_ITEM_H