/* ------------------------------------------------------
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
Date    Sat Feb 19 2022

Workshop 5 part 2
Module: Portfolio
Desc:   Module for Portfolio object and functions
Filename: Portfolio.cpp
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS

#include "Portfolio.h"

using namespace std;
namespace sdds {

    Portfolio::Portfolio() {
       emptyPortfolio();
    }

    void Portfolio::emptyPortfolio()
    {
        m_value = 0;
        m_stock[0] = 0;
        m_type = 'E';
    }
    Portfolio::Portfolio(double value, const char* stock, char type) {
        emptyPortfolio();
        if (value >= 0 && ( type == 'V' || type == 'G' || type == 'I') ) {
            m_value = value;
            m_type = type;
            strcpy(m_stock, stock);
        }
    }

    void Portfolio::dispPortfolio() const{
            cout << " ";
            cout.width(10);
            cout << (const char*)(*this);
            cout << " | ";
            cout << "Value: ";
            cout.width(10);
            cout << double(*this);
            cout << " | ";
            cout << " Type: ";
            cout << char(*this);
    }
    std::ostream& Portfolio::display() const {

        if (~*this) {
            cout << " Portfolio  |  Bad-NG |";
            dispPortfolio();
        }
        else if (*this) {
            cout << " Portfolio  |  Active |";
            dispPortfolio();

        }
        else {
            cout << " Portfolio  |  EMPTY  |";
            dispPortfolio();
        }
        return cout;
    }

    Portfolio::operator double() const {
        return m_value;
    }

    Portfolio::operator const char* () const {
        return m_stock;
    }

    Portfolio::operator char() const {
        return m_type;
    }

    Portfolio::operator bool() const {
        return (m_type == 'G' || m_type == 'V' || m_type == 'I');   // true if investment type is initiated valid type
    }

    Portfolio& Portfolio::operator+=(double value) {
        if (value > 0 && *this) {  // proceed only if value and object are valid
            m_value += value;
        }
        return *this;
    }

    Portfolio& Portfolio::operator-=(double value) {
        if (value < 0 && *this) {  // proceed only if value and object are valid
            m_value -= value;

            // set portfolio to empty if value is now <= 0
            if (m_value <= 0) {
                emptyPortfolio();
            }
        }
        return *this;
    }

    bool Portfolio::operator~() const {
        return m_value < 0;     // true if object has invalid (negative) m_value
    }

    Portfolio& Portfolio::operator<<(Portfolio& moveFrom) {
        // only proceed if the argument object is not the current object and both objects are valid
        if (this != &moveFrom && *this && moveFrom) {
            m_value += (double)moveFrom;    // increment value of current object by value of argument object
            moveFrom.emptyPortfolio();               // set argument object to empty
        }
        return *this;
    }

    Portfolio& Portfolio::operator>>(Portfolio& moveTo) {
        // only proceed if the argument object is not the current object and both objects are valid
        if (this != &moveTo && *this && moveTo) {
            moveTo += m_value;      // increment value of argument object by value of current object
            emptyPortfolio();       // set current object to empty
        }
        return *this;
    }

    double operator+(const Portfolio& portfolioA, const Portfolio& portfolioB) {
        double sum = 0;    // returns 0 if if either object is false
        if (portfolioA && portfolioB) {
            sum = (double)portfolioA + (double)portfolioB;
        }
        return sum;
    }

    double operator+=(double& numPtr, const Portfolio& portfolio) {
        numPtr += (double)portfolio;
        return numPtr;
    }
}