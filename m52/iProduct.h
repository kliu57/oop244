/* ------------------------------------------------------
Final Project Milestone 5
Module: iProduct
Filestatus: iProduct.h
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_IPRODUCT_H
#define SDDS_IPRODUCT_H
#include <iostream>
#include <fstream>
namespace sdds {
    // An interface for an Item in the application
    class iProduct {

    public:
        // destructor
        virtual ~iProduct() = 0;

        // to read the Stock-Keeping Unit from console before
        // main data entry
        virtual int readSku(std::istream& istr) = 0;

        // to reduce the quantity on hand
        virtual int operator-=(int qty) = 0;

        // to increase the quantity on hand
        virtual int operator+=(int qty) = 0;

        // returns the price of the produce
        virtual operator double() const = 0;

        // returns if the iProduct is in a good state
        virtual operator bool() const = 0;

        // returns the number of products needed
        virtual int qtyNeeded() const = 0;

        // retuns the quantity on hand
        virtual int qty() const = 0;

        // determines if the iProduct is displayed in a linear format or 
        // descriptive format
        virtual void linear(bool isLinear) = 0;

        // saves the iProduct into a file
        virtual std::ofstream& save(std::ofstream& ofstr) const = 0;

        // loads an iProduct from a file
        virtual std::ifstream& load(std::ifstream& ifstr) = 0;

        // displays the iProduct on the screen
        virtual std::ostream& display(std::ostream& ostr) const = 0;

        // reads the iProduct from the console
        virtual std::istream& read(std::istream& istr) = 0;

        // return true if the sku is a match to the iProduct's sku
        virtual bool operator==(int sku) const = 0;

        // retrns true if the description is found in the iProduct's description
        virtual bool operator==(const char* description) const = 0;
    };

    // insertion operator overload
    // returns the display method of the iProduct argument
    std::ostream& operator<<(std::ostream& ostr, const iProduct& ipObject);

    // extraction operator overload
    // returns the read method of the iProduct argument
    std::istream& operator>>(std::istream& istr, iProduct& ipObject);
}
#endif // !SDDS_IPRODUCT_H