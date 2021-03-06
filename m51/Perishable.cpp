/* ------------------------------------------------------
Final Project Milestone 5
Module: Perishable
Filestatus: Perishable.cpp
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
#include "Perishable.h"
#include "Utils.h"
using namespace std;

namespace sdds {
    // private member functions

    void Perishable::setEmpty() {
        delete [] m_instr;
        m_instr = nullptr;
    }

    // public member functions

    Perishable::Perishable() : Item() {
        m_instr = nullptr;
    }

    Perishable::~Perishable() {
        delete [] m_instr;
    }

    Perishable::Perishable(const Perishable& perishableObject) : Item(perishableObject) {
        *this = perishableObject;
    }

    Perishable& Perishable::operator=(const Perishable& perishableObject) {
       
        Item::operator=(perishableObject);	                // calls base class assignment operator

        if (this != &perishableObject) {	// check that addresses are not the same and perishableObject is valid
            ut.alocpy(m_instr, perishableObject.m_instr);       // copy instr safely dynamically
            m_expiryDate = perishableObject.m_expiryDate;       // copy Date object
        } else {
            setEmpty();
        }
        return *this;
    }

    Date Perishable::expiry() const {
        return m_expiryDate;
    }

    ofstream& Perishable::save(ofstream& ofstr) const {
        Date expDate = m_expiryDate;
        if (Item::m_state) {    // only proceed if state is good
            expDate = expDate.formatted(false);
            Item::save(ofstr) << '\t';              // call base class save
            ofstr << ((m_instr != nullptr) ? m_instr : "") << '\t';
            ofstr << expDate;
        }

        return ofstr;
    }

    ifstream& Perishable::load(ifstream& ifstr) {
        bool validInput = false;
        bool error = false;
        int expDateNum = 0;

        // call base class load
        Item::load(ifstr);      

        // check for errors after base class load
        if (!error) {
            if (!Item::m_state) error = true;
        }

        // 1. check tab
        if (!error) {
            if (ifstr.peek() == '\t') {
                ifstr.ignore();
            } else {
                error = true;
            }
        }

        // 2. read next thing which should be instructions
        if (!error) {
            ut.getFileCstring(m_instr, ifstr, '\t');    //this already throws away the tab
        }
     
        // 2. check for errors after read
        if (!error) {
            if (ifstr.fail() || ifstr.eof()) error = true;
        }

        // 2. after tab ignore check for eof or newline
        if (!error) {
            if (ifstr.fail() || ifstr.eof()) error = true;
        }
        if (!error) {
            if (ifstr.peek() == '\n') error = true;
        }

        // 3. read next thing which should be expiry date in form of 6 digit number
        if (!error) {
            ifstr >> expDateNum;
        }

        // 3. check for errors after read
        if (!error) {
            if (ifstr.fail() || ifstr.eof()) error = true;
        }
        if (!error) {
            if (expDateNum < 100000 || expDateNum > 999999) error = true;
        }

        // 3. store the date
        if (!error) {
            m_expiryDate = Date(expDateNum);
        }
        if (!error) {
            if (!m_expiryDate) error = true;
        }

        // 4. check that ends with a newline character, ignore newline character
        if (!error) {
            if (ifstr.peek() != '\n') {
                error = true;
            } else {
                ifstr.ignore();	// throw away newline

                // reached the end, success
                validInput = true;
            }
        }

        if (validInput) {
            ifstr.clear();  // clears state to allow further extraction

        } else {
            // invalid input read, clear buffer
            ifstr.clear();
            if (ifstr.peek() != '\n') ifstr.ignore(1000, '\n');

            m_state = "Input file stream read (perishable) failed!"; // set state to bad
        }

        return ifstr;
    }

    ostream& Perishable::display(ostream& ostr) const {
        Date expDate = m_expiryDate;

        if (Item::m_state) {
            // state is good, print SKU, instrription, on-hand quantity, needed quantity, price, expiry date
            if (Item::linear()) {       // linear format
                expDate.formatted(true);
                Item::display(ostr);    // call base class display

                // print asterix if perishable has instructions
                if (m_instr != nullptr) {
                    ostr << '*';
                } else {
                    ostr << ' ';
                }

                ostr << expDate;

            } else {    // descriptive format
               expDate.formatted(true);
                ostr << "Perishable ";
                Item::display(ostr);    // call base class display
                ostr << "Expiry date: " << expDate;
                if (m_instr != nullptr) {
                    ostr << "\nHandling Instructions: " << m_instr;
                }
                ostr << endl;
            }
        } else {
            ostr << (const char*)m_state;   // print state since bad
        }

        return ostr;
    }

    int Perishable::readSku(istream& istr) {
        m_sku = ut.getint(10000, 39999, "SKU: ", "Invalid Integer", istr);
        return m_sku;
    }

    istream& Perishable::read(istream& istr) {
        int expDateNum;

        Item::read(istr);       // call base class read

        delete [] m_instr;   // delete instr
        m_instr = nullptr;

        expDateNum = ut.getint(100000, 999999, "Expiry date (YYMMDD): ", nullptr, istr); // prompt for expiry date
        m_expiryDate = Date(expDateNum);    // create date object

        cout << "Handling Instructions, ENTER to skip: ";   // prompt for <ENTER>

        if (istr.peek() != '\n') {
            ut.getcstring(m_instr, istr);    // get instr

        } else {    // skip reading instr
            delete [] m_instr;
            m_instr = nullptr;
        }

        // set item state to failed if stream failed or date is invalid
        if (istr.fail() || !m_expiryDate) {
            m_state = "Perishable console date entry failed!";
        }

        return istr;
    }
}