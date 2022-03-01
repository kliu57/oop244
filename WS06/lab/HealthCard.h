/* ------------------------------------------------------
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
Date    Tue Mar 01 2022

Workshop 6 part 1
Module: HealthCard
Desc:   Module for HealthCard object and functions
Filename: HealthCard.h
-----------------------------------------------------------*/
#ifndef SDDS_HEALTHCARD_H
#define SDDS_HEALTHCARD_H
#include <cstring>
#include <iostream>
#include <istream>

namespace sdds {
   const int MaxNameLength = 55;
   const int VCodeLength = 2;
   const int SNumberLength = 9;
   class HealthCard {
      char* m_name{};       // name of cardholder - to be dynamically allocated
      long long m_number;   // number of card
      char m_vCode[VCodeLength+1];     // version code of card
      char m_sNumber[SNumberLength+1];    // stock control number

      // Returns true is the four parts of the ID card are valid
      bool validID(const char* name, long long number, const char vCode[] , const char sNumber[]) const;

      // Sets the HeathCard object to a recognizable empty (invalid) state by setting m_name to nullptr
      void setEmpty();

      // Free the memory pointed by m_name
      // Allocate enough memory to store name Cstring
      // Copy the Cstring pointed by name into the newly allocated memory pointed by m_name
      void allocateAndCopy(const char* name);

      // "peek()" and see if the next character in the keyboard buffer is the same as the ch argument
      // If it is the same, Remove it from the keyboard and throw it away! (i.e. istr.ignore())
      // If not:
      // Ignore all the remaining characters (up to 1000 characters) or the value of ch (use istr.ignore(int n,char c))
      // Set the istream into a fail state (use istr.setstate(iso::failbit))
      void extractChar(std::istream& istr, char ch) const;

      // Inserts the three parts related to the main card number, version code and stock number of the health card information into the istr object in the following format:
      // 1234567890-AB, XY7652341
      // and then returns the istr object reference ostream& printIDInfo(ostream& ostr)const;
      std::ostream& printIDInfo(std::ostream& ostr) const;

      // Validates the arguments, reallocates memory for the name and sets the object attributes to their corresponding values.
      // If the name and the three parts are valid (see Validation) call the private function to validate
      // Calls the reallocateAndCopy function to set the name
      // Sets the three parts to their values (m_number, m_vCode, m_sNumber)
      // If not, it deletes the memory pointed by m_name and sets the object to a safe empty state (setEmpty())
      void set(const char* name, long long number, const char vCode[], const char sNumber[]);
   public:
       // constructor
       HealthCard(const char* name = nullptr, long long number = 0, const char vCode[] = {}, const char sNumber[] = {});

       // destructor
       // deletes the memory pointed by m_name
       ~HealthCard();

       // copy constructor
       // if the hc object is valid it will set the values of the current object to those of the incoming argument (hc using assignment to *this)
       HealthCard(const HealthCard& hc);

       // Copy Assignment operator overload
       // First, it will make sure that this is not a "self-copy" by comparing the address of the current object and the address of the incoming argument
       // If it is not a self copy this function works exactly like the copy constructor
       // If it is a self copy don't perform any action At the end return the reference of the current object
       HealthCard& operator=(const HealthCard& hc);

       // Boolean type conversion operator
       // Returns true if m_name is not nullptr, else it will return false
       operator bool() const;

       /*
       If the current object is in a valid state it inserts the values of the card information in two different formats based on the value of the toFile argument :
       if toFile is true, prints the data in a comma-separated format:
       prints the name
           print comma
           print the health card ID information using the private function printIDInfo
           if toFile is false prints the data in the following format:
       In 50 characters, left-justified and padded with dots ('.'): prints the name
           print the health card ID information using the private function printIDInfo
           At the end, it returns the ostr reference
       */
       std::ostream& print(std::ostream& ostr, bool toFile = true) const;

       // Reads the Contact information in following format:
       // Example: Luke Skywalker,1231231234-XL,AF1234567
       std::istream& read(std::istream& istr);
   };

   // insertion operator overload
   // if hc is valid it will print it using the print function on the screen and not on File, (i.e. onFile is false). Otherwise, it will print "Invalid Card Number".
   // In the end, it will return the ostr reference.
   std::ostream& operator<<(std::ostream& ostr, const HealthCard& hc);

   // extraction operator overload
   // returns the read method of the hc argument.
   std::istream& operator>>(std::istream& istr, HealthCard& hc);
}
#endif // !SDDS_HealthCard_H