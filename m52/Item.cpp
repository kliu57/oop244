/* ------------------------------------------------------
Final Project Milestone 5
Module: Item
Filestatus: Item.cpp
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define  _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <string>
#include <iomanip>
#include "Item.h"
#include "Utils.h"
using namespace std;

namespace sdds {
    // private member functions

    void Item::setEmpty() {
        delete [] m_desc;
        m_desc = nullptr;
        m_qty = 0;
        m_qtyNeeded = 0;
        m_price = 0;
        m_isLinear = false;
        m_sku = 0;
        clear();    // clear state
    }

    // protected member functions

    bool Item::linear() const {
        return m_isLinear;
    }

    // public member functions

    Item::Item() : iProduct() {
        m_desc = nullptr;
        m_qty = 0;
        m_qtyNeeded = 0;
        m_price = 0;
        m_isLinear = false;
        m_sku = 0;
    }

    Item::~Item() {
        delete [] m_desc;
    }

    Item::Item(const Item& itemObject) : iProduct() {
        if (itemObject) {
            *this = itemObject;
        } else {
            setEmpty();
        }
    }

    Item& Item::operator=(const Item& itemObject) {
        if (this != &itemObject && itemObject) {	// check that addresses are not the same and itemObject is valid
            ut.alocpy(m_desc, itemObject.m_desc);   // copy desc safely dynamically
            m_qty = itemObject.m_qty;
            m_qtyNeeded = itemObject.m_qtyNeeded;
            m_price = itemObject.m_price;
            m_isLinear = itemObject.m_isLinear;
            m_sku = itemObject.m_sku;
            m_state = itemObject.m_state;           // copy Status object
        } else {
            setEmpty();
        }
        return *this;
    }

    int Item::qtyNeeded() const {
        return m_qtyNeeded;
    }

    int Item::qty() const {
        return m_qty;
    }

    Item::operator double() const {
        return m_price;
    }

    Item::operator bool() const {
        return m_state && (m_desc != nullptr);
    }

    void Item::clear() {
        m_state.clear();
    }

    int Item::operator-=(int qty) {
        m_qty = (m_qty > qty) ? m_qty - qty : 0;    // don't reduce past zero
        return m_qty;
    }

    int Item::operator+=(int qty) {
        m_qty += qty;
        return m_qty;
    }

    void Item::linear(bool isLinear) {
        m_isLinear = isLinear;
    }

    bool Item::operator==(int sku) const {
        bool match = false;
        if (m_sku == sku) {
            match = true;
        }
        return match;
    }

    bool Item::operator==(const char* description) const {
        bool match = false;
        if (description != nullptr && m_desc != nullptr) {
            if (ut.findInCstring(m_desc, description)) {
                match = true;
            }
        }
        return match;
    }

    ofstream& Item::save(ofstream& ofstr) const {
        if (*this) {  // only proceed if item is valid
            ofstr << m_sku << '\t';
            ofstr << m_desc << '\t';
            ofstr << m_qty << '\t';
            ofstr << m_qtyNeeded << '\t';
            ofstr << m_price;
        }
        return ofstr;
    }

    ifstream& Item::load(ifstream& ifstr) {
		bool validInput = false;
        bool error = false;

        setEmpty(); // set object to empty state

        // if stream already ended or starts with a newline then error out
        if (!error) {
            if (ifstr.eof()) error = true;
        }
        if (!error) {
            if (ifstr.peek() == '\n') error = true;
        }

		// 1. read first thing which should be sku
        if (!error) {
            ifstr >> m_sku;
        }

        // 1. check for errors after read
        if (!error) {
            if (ifstr.fail() || ifstr.eof()) error = true;
        }
        if (!error) {
            if (m_sku <= 0) error = true;
        }

        // 1. ignore tab
        if (!error) {
            if (ifstr.peek() != '\t') {
                error = true;
            } else {
                ifstr.ignore();	// throw away tab
            }
        }

        // 1. after tab ignore check for eof or newline
        if (!error) {
            if (ifstr.fail() || ifstr.eof()) error = true;
        }
        if (!error) {
            if (ifstr.peek() == '\n') error = true;
        }

        // 2. read second thing which should be description
        if (!error) {
            ut.getFileCstring(m_desc, ifstr, '\t');     // this already throws away the tab
        }

        // 2. check for errors after read
        if (!error) {
            if (ifstr.fail() || ifstr.eof()) error = true;
        }
        if (!error) {
            if (m_desc == nullptr) error = true;
        }

        // 2. after tab ignore check for eof or newline
        if (!error) {
            if (ifstr.fail() || ifstr.eof()) error = true;
        }
        if (!error) {
            if (ifstr.peek() == '\n') error = true;
        }

        // 3. read third thing which should be qty
        if (!error) {
            ifstr >> m_qty;
        }

        // 3. check for errors after read
        if (!error) {
            if (ifstr.fail() || ifstr.eof()) error = true;
        }
        if (!error) {
            if (m_qty < 0) error = true;
        }
        
        // 3. ignore tab
        if (!error) {
            if (ifstr.peek() != '\t') {
                error = true;
            } else {
                ifstr.ignore();	// throw away tab
            }
        }

        // 3. after tab ignore check for eof or newline
        if (!error) {
            if (ifstr.fail() || ifstr.eof()) error = true;
        }
        if (!error) {
            if (ifstr.peek() == '\n') error = true;
        }

        // 4. read fourth thing which should be qty needed
        if (!error) {
            ifstr >> m_qtyNeeded;
        }

        // 4. check for errors after read
        if (!error) {
            if (ifstr.fail() || ifstr.eof()) error = true;
        }
        if (!error) {
            if (m_qtyNeeded < 0) error = true;
        }

        // 4. ignore tab
        if (!error) {
            if (ifstr.peek() != '\t') {
                error = true;
            } else {
                ifstr.ignore();	// throw away tab
            }
        }

        // 4. after tab ignore check for eof or newline
        if (!error) {
            if (ifstr.fail() || ifstr.eof()) error = true;
        }
        if (!error) {
            if (ifstr.peek() == '\n') error = true;
        }

        // 5. read fifth thing which should be price
        if (!error) {
            ifstr >> m_price;
        }

        // 5. check for errors after read
        if (!error) {
            if (ifstr.fail() || ifstr.eof()) error = true;
        }
        if (!error) {
            if (m_price < 0) error = true;
        }

        // 5. check that ends with a newline character, ignore newline character
        if (!error) {
            if (ifstr.peek() == '\n') {
                ifstr.ignore();	// throw away newline

                // reached the end, success
                validInput = true;

            } else if (ifstr.peek() == '\t')  {
                // reached the end, success
                validInput = true;
            } else {
                error = true;
            }
        }

		if (validInput) {
            clear();    // clear state
            ifstr.clear();				// clears state to allow further extraction

		} else {
            // invalid input read, clear buffer
            ifstr.clear();
            if (ifstr.peek() != '\n') ifstr.ignore(1000, '\n');

            m_state = "Input file stream read failed!"; // set state to bad
		}

		return ifstr;
    }

    ostream& Item::display(ostream& ostr) const {
        const int descWidth = 35;
        double neededFunds = 0.0;
        char tempDesc[descWidth+1];
        if (*this) {
            // item is valid, print SKU, description, on-hand quantity, needed quantity and price
            if (m_isLinear) {   // linear format
                ostr << left << setw(4) << m_sku << " | ";

                // if length supasses descWidth, crop desc for printing to 35 characters
                if (static_cast<int>(strlen(m_desc)) > descWidth) {
                    strncpy(tempDesc, m_desc, descWidth);
                    tempDesc[descWidth] = '\0';
                    ostr << setw(descWidth) << tempDesc << " | ";  // print cropped version
                } else {
                    ostr << setw(descWidth) << m_desc << " | ";    // print regular version
                }

                ostr.unsetf(ios::left);
                ostr << setw(4) << m_qty << " | ";
                ostr << setw(4) << m_qtyNeeded << " | ";
                ostr << setw(7) << fixed << setprecision(2) << m_price << " |";
                ostr.unsetf(ios::fixed);
                ostr.precision(6);
            } else {    // descriptive format
                if (m_qtyNeeded > m_qty) {
                    neededFunds = ((double)m_qtyNeeded - (double)m_qty) * m_price;
                }
                ostr << "AMA Item:" << endl;
                ostr << m_sku << ": " << ((m_desc != nullptr) ? m_desc : "") << endl;
                ostr << "Quantity Needed: " << m_qtyNeeded << endl;
                ostr << "Quantity Available: " << m_qty << endl;
                ostr << "Unit Price: $" << fixed << setprecision(2) << m_price << endl;
                ostr << "Needed Purchase Fund: $" << neededFunds << endl;
                ostr.unsetf(ios::fixed);
                ostr.precision(6);
            }
        } else {
            ostr << m_state;   // print state since bad
        }

        return ostr;
    }

    int Item::readSku(istream& istr) {
        m_sku = ut.getint(40000, 99999, "SKU: ", "Invalid Integer", istr);
        return m_sku;
    }

    istream& Item::read(istream& istr) {
        delete [] m_desc;   // delete desc
        m_desc = nullptr;
        clear();    // clear state

        cout << "AMA Item:" << endl;
        cout << "SKU: " << m_sku << endl;   // display the sku

        ut.getcstring(m_desc, "Description: ", "Invalid description");  // get desc

        m_qtyNeeded = ut.getint(1, 9999, "Quantity Needed: ", "Invalid Integer");   // prompt/get qty needed
        m_qty = ut.getint(0, m_qtyNeeded, "Quantity On Hand: ", "Invalid Integer"); // prompt/get qty
        m_price = ut.getdouble(0.0, 9999.0, "Unit Price: $", "Invalid number");     // prompt/get price

        // set item state to fail if desc is invalid or stream failed
        if (istr.fail() || m_desc == nullptr) {
            m_state = "Console entry failed!";
        }
        
        return istr;
    }
}