/* ------------------------------------------------------
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
Date    Thu Feb 17 2022

Workshop 5 part 1
Module: Flight
Desc:   Module for Flight object and functions
Filename: Flight.cpp
-----------------------------------------------------------*/
#ifndef SDDS_FLIGHT_H
#define SDDS_FLIGHT_H
#include <iostream>
#include <string>

namespace sdds {

   const int Boen747Capacity = 388;
   const int FuelTankCapacity = 238840;
   const double minFuelPerPassenger = 600;

   class Flight {

      int m_passengers = 0;
      double m_fuel = 0;
      char m_title[16];
      void emptyPlane();

   public:
      Flight();
      Flight(int passengers, double fuel, const char* title);
      std::ostream& display()const;

      // return true if flight non-empty and fuel not low fuel
      explicit operator bool() const;

      // returns flight number of passengers
      operator int() const;

      // returns flight fuel
      explicit operator double() const;

      // returns flight title
      // NOTE: THIS IS NOT REQUIRED BY ASSIGNMENT INSTRUCTIONS BUT IT IS CALLED BY TESTING PROGRAM
      operator const char*() const;

      // returns flight title
      operator const std::string() const;

      // returns true if the Flight number of passengers is 0, otherwise false
      bool operator ~() const;

      // set current Flight object to argument Flight object
      // set argument Flight object to empty
      // returns reference to current Flight object
      Flight& operator=(Flight& assignTo);

      // set number of passengers to argument integer if the integer is a valid passenger number value
      // returns reference to current Flight object
      Flight& operator=(int passengers);

      // set fuel to argument double if the double is a valid fuel value
      // returns reference to current Flight object
      Flight& operator=(double fuel);

      // add to fuel by argument double if the double is positive
      // if new fuel value is over capacity set fuel to capacity
      // returns reference to current Flight object
      Flight& operator+=(double fuel);

      // add to passenger number by argument integer if the integer is positive
      // if new passenger value is over capacity set passenger to capacity
      // returns reference to current Flight object
      Flight& operator+=(int passengers);

      // decrease fuel by argument double if the double is positive
      // if new fuel value is below 0 set fuel to 0
      // returns reference to current Flight object
      Flight& operator-=(double fuel);

      // decrease passenger number by argument integer if the integer is positive
      // if new passenger value is below 0 set passenger to 0
      // returns reference to current Flight object
      Flight& operator-=(int passengers);

      // move passengers from argument flight to this flight
      // only move up to the max amount of passengers in this flight
      // returns reference to current Flight object
      Flight& operator<<(Flight &moveFrom);

      // move passengers from this flight to the argument flight
      // only move up to the max amount of passengers in argument flight
      // returns reference to current Flight object
      Flight& operator>>(Flight &moveTo);
   };

   // returns the sum of the number of passengers of the two Flights
   // If any of the two Flights don't evaluate to TRUE, then zero is returned
   int operator+(const Flight& flightA, const Flight& flightB);

   // adds num passengers from flight to number stored at integer pointer
   // returns integer value stored at pointer
   int operator+=(int* numPtr, const Flight& flight);
}
#endif // SDDS_FLIGHT_H