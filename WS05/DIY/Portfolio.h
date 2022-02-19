/* ------------------------------------------------------
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
Date    Sat Feb 19 2022

Workshop 5 part 2
Module: Portfolio
Desc:   Module for Portfolio object and functions
Filename: Portfolio.h
-----------------------------------------------------------*/
#ifndef SDDS_Portfolio_H_
#define SDDS_Portfolio_H_
#include <iostream>
#include <string>

namespace sdds {

   class Portfolio {
      double m_value = 0;
      char m_stock[16];
      char m_type;
      // set object to safe empty state
      void emptyPortfolio();

   public:
       Portfolio();
       Portfolio(double value, const char* stock, char type);

       // prints "Bad-NG" if value is negative, "Active" if investment type is 'G' 'V' or 'I', "EMPTY" otherwise
       // followed by portfolio details
       void dispPortfolio() const;

       // prints portfolio details
       std::ostream& display()const;

       // cast object to double, returns Portfolio value
       operator double() const;

       // cast object to char*, returns stock name
       operator const char*() const;

       // cast object to char, returns investment type
       operator char() const;

       // cast object to bool, returns true if the type of the investment type is 'G', 'V or 'I', otherwise false
       operator bool() const;

       // increase Portfolio value
       // action is omitted if current object is not true or argument is negative
       // returns reference to current object
       Portfolio& operator+=(double value);

       // decrease Portfolio value
       // action is omitted if current object is not true or argument is negative
       // returns reference to current object
       Portfolio& operator-=(double value);

       // returns true if Portfolio value is negative, otherwise false
       bool operator ~() const;

       // move Portfolio value from argument Portfolio to current object
       // action is omitted if current or argument object is not true
       // returns reference to current Portfolio object
       Portfolio& operator<<(Portfolio& moveFrom);

       // move Portfolio value from current object to argument Portfolio
       // action is omitted if current or argument object is not true
       // returns reference to current Portfolio object
       Portfolio& operator>>(Portfolio& moveTo);
   };

   // returns the sum of the values of the two Portfolios
   // return 0 if any of the two Portfolios is not true
   double operator+(const Portfolio& portfolioA, const Portfolio& portfolioB);

   // adds value from portfolio object to double stored at pointer
   // returns double value stored at pointer
   double operator+=(double& numPtr, const Portfolio& portfolio);
}
#endif // SDDS_Portfolio_H_