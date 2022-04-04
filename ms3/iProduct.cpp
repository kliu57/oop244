/* ------------------------------------------------------
Final Project Milestone 3
Module: iProduct
Filestatus: iProduct.cpp
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
-----------------------------------------------------------
I have done all the coding by myself and only copied the code 
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define  _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "iProduct.h"
#include "Utils.h"
using namespace std;

namespace sdds {

    iProduct::~iProduct() {
        // this is only here because my Visual Studios complains when it is not
    }

    // helper functions

    ostream& operator<<(ostream& ostr, const iProduct& ipObject) {
        return ipObject.display(ostr);
    }

    istream& operator>>(istream& istr, iProduct& ipObject) {
        return ipObject.read(istr);
    }
}