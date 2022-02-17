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
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include "Flight.h"

using namespace std;
namespace sdds {

    void Flight::emptyPlane() {
        m_passengers = 0;
        m_fuel = 0;
        strcpy(m_title , "EmptyPlane");
    }

    // New Flight
    Flight::Flight() {
        emptyPlane();
    }
    Flight::Flight(int passengers, double fuel, const char* title) {
        emptyPlane();
        if (passengers > 0 && passengers <= Boen747Capacity && fuel >= 0 &&
            fuel <= FuelTankCapacity) {
            m_passengers = passengers;
            m_fuel = fuel;
            if (m_title != title) { strcpy(m_title,title); }    // added error checking to prevent it from copying to itself
        }
    }
    std::ostream& Flight::display() const {

        if (*this) {
            cout << " Flight  |  Ready to Depart";
            cout << " ";
            cout.width(10);
            cout << std::string(*this);
            cout << " | ";
            cout << "Pass: ";
            cout.width(10);
            cout << int(*this);
            cout << " | ";
            cout.width(12);
            cout.precision(2);
            cout.setf(ios::right);
            cout.setf(ios::fixed);
            cout << double(*this);
            cout.unsetf(ios::right);
            cout << " Liters";
        }
        else if (~*this) {
            cout << " Flight  |  Empty Plane    ";
        }
        else {
            cout << " Flight  |  Low Fuel       ";
            cout << " ";
            cout.width(10);
            cout << (const char *)(*this);
            cout << " | ";
            cout << "Pass: ";
            cout.width(10);
            cout << int(*this);
            cout << " | ";
            cout.width(12);
            cout.precision(2);
            cout.setf(ios::right);
            cout.setf(ios::fixed);
            cout << double(*this);
            cout.unsetf(ios::right);
            cout << " Liters";
        }
        return cout;
    }

    Flight::operator bool() const {
        return (m_passengers > 0 && m_fuel >= minFuelPerPassenger * (double)m_passengers); 
    } 

   Flight::operator int() const {
        return m_passengers;
    }

   Flight::operator double() const {
        return m_fuel;
    }

    Flight::operator const char*() const {
        return m_title;
    }

    Flight::operator const std::string() const {
        return m_title;
    }

    bool Flight::operator ~() const {
        return bool(m_passengers == 0);
    }

    Flight& Flight::operator=(Flight& assignTo) {
        emptyPlane();   // set current object to empty
        int passengers = (int)assignTo;
        double fuel = (double)assignTo;
        // set current flight object to argument object if argument object is valid
        if (passengers > 0 && passengers <= Boen747Capacity && fuel >= 0 &&
            fuel <= FuelTankCapacity) {
            m_passengers = passengers;
            m_fuel = fuel;
            strcpy(m_title, (const char*)assignTo);
        }
        // set argument object to empty
        assignTo.emptyPlane();
        return *this;
    }

    Flight& Flight::operator=(int passengers) {
        if (passengers > 0 && passengers <= Boen747Capacity) {
            m_passengers = passengers;
        }
        return *this;
    }

    Flight& Flight::operator=(double fuel) {
        if (fuel >= 0 && fuel <= FuelTankCapacity) {
            m_fuel = fuel;
        }
        return *this;
    }

    Flight& Flight::operator+=(double fuel) {
        double newFuelValue = 0;
        if (fuel > 0) { // proceed if fuel addition is not negative
            newFuelValue = m_fuel + fuel;
            // check if new fuel value is over capacity
            if (newFuelValue > FuelTankCapacity) {
                m_fuel = FuelTankCapacity;  // fill to capacity
            } else {
                m_fuel = newFuelValue;      // fill to new value
            }
        }
        return *this;
    }

    Flight& Flight::operator+=(int passengers) {
        int newNumPassengers = 0;
        if (passengers > 0) { // proceed if passenger addition is not negative
            newNumPassengers = m_passengers + passengers;
            // check if new passenger value is over capacity
            if (newNumPassengers > Boen747Capacity) {
                m_passengers = FuelTankCapacity;      // fill to capacity
            } else {
                m_passengers = newNumPassengers;      // fill to new value
            }
        }
        return *this;
    }

    Flight& Flight::operator-=(double fuel) {
        double newFuelValue = 0;
        if (fuel > 0) { // proceed if fuel addition is not negative
            newFuelValue = m_fuel - fuel;
            // check if new fuel value is below 0
            if (newFuelValue < 0) {
                m_fuel = FuelTankCapacity;  // set to 0
            } else {
                m_fuel = newFuelValue;      // set fuel to new value
            }
        }
        return *this;
    }

    Flight& Flight::operator-=(int passengers) {
        int newNumPassengers = 0;
        if (passengers > 0) { // proceed if passenger addition is not negative
            newNumPassengers = m_passengers - passengers;
            // check if new passenger value is over capcity
            if (newNumPassengers < 0) {
                m_passengers = FuelTankCapacity;      // deplane until empty
            } else {
                m_passengers = newNumPassengers;      // set number of passengers to new value
            }
        }
        return *this;
    }

    Flight& Flight::operator<<(Flight &moveFrom) {
        int space = 0;
        int moveWaitlist = 0;
        int numMoved = 0;   // will store the number of people actually moved over
        // only proceed if the argument flight is not the current object and both objects are valid
        if (!(*this = moveFrom) && *this && moveFrom) {
            space = Boen747Capacity - m_passengers; // space is number of free seats in this flight object
            moveWaitlist = (int)moveFrom;           // waitlist number is number of people in argument flight
            // check if there is space to move everyone who wants to move
            if (space < moveWaitlist) {
                m_passengers = Boen747Capacity;     // fill to max
                numMoved = space;                   // number of people moved is equal to available space
            } else {
                m_passengers += moveWaitlist;       // incremement passengers by waitlist amount
                numMoved = moveWaitlist;            // number of people moved is equal to waitlist amount
            }
            moveFrom -= numMoved;   // decrement passengers off argument flight
        }
        return *this;
    }

    Flight& Flight::operator>>(Flight &moveTo) {
        int space = 0;
        int moveWaitlist = 0;
        int numMoved = 0;   // will store the number of people actually moved over
        // only proceed if the argument flight is not the current object and both objects are valid
        if (!(*this = moveTo) && *this && moveTo) {

            space = Boen747Capacity - (int)moveTo;  // space is number of free seats in argument flight
            moveWaitlist = m_passengers;            // waitlist number is number of people in this flight

            // check if there is space to move everyone who wants to move
            if (space < moveWaitlist) {
                moveTo += space;                    // increment passengers by the amount of space
                numMoved = space;                   // number of people moved is equal to available space
            } else {
                moveTo += moveWaitlist;             // incremement passengers by waitlist amount
                numMoved = moveWaitlist;            // number of people moved is equal to waitlist amount
            }
            m_passengers -= numMoved;   // decrement passengers off this flight
        }
        return *this;
    }

    // PUBLIC HELPER FUNCTIONS

    int operator+(const Flight& flightA, const Flight& flightB) {
        int sum = 0;
        if (*flightA && *flightB) {
            sum = (int)*flightA + (int)*flightB;
        }
        return sum;
    }

    int operator+=(int* numPtr, const Flight& flight) {
        *numPtr += (int)flight;
        return *numPtr;
    }
}