/* ------------------------------------------------------
Author	Katie Liu
Email   kliu57@myseneca.ca
ID      018889121
Date    Thu Feb 10 2022

Workshop 4 part 1
Module: CarInventory
Desc:   Module for CarInventory object and functions
Filename: CarInventory.h
-----------------------------------------------------------*/

#ifndef SDDS_CARINVENTORY_H
#define SDDS_CARINVENTORY_H 

namespace sdds {

    const int MIN_YEAR = 1990;
    const int MIN_CODE = 100;
    const int MAX_CODE = 999;

    class CarInventory {
        char* m_type;
        char* m_brand;
        char* m_model;
        int m_year;
        int m_code;
        double m_price;

        // initialize all member variables to safe empty state
        void resetInfo();

        // deallocate memory fpr type, brand, model
        void deallocMemory();

        // checks a set of car info to see if it passes validation
        bool validateCarInfo(const char* type, const char* brand, const char* model, int year, int code, double price) const;

    public:

        // initialize member variables
        CarInventory();

        // Dynamically store type, brand, model arguments in corresponding member variables
        // Store year, code, price arguments in corresponding member variables if provided and pass validation
        // If any argument provided does not pass validation the object will be set to safe empty state
        CarInventory(const char* type, const char* brand, const char* model, int year = 2022, int code = 100, double price = 1);

        // deallocate the dynamically allocated memory in type, brand, and model
        ~CarInventory();

        // checks whether this object has valid values
        bool isValid() const;

        // returns type
        char* getType() const;

        // returns brand
        char* getBrand() const;

        // returns model
        char* getModel() const;

        // returns year
        int getYear() const;

        // first deallocate all the allocated memory and then sets the attributes to the corresponding arguments exactly like the 6 argument constructor
        // Returns the reference of the current object
        CarInventory& setInfo(const char* type, const char* brand, const char* model, int year, int code, double price);

        // prints the values of all the member variables
        void printInfo() const;

        // check whether type, brand, model, year of another instance of CarInventory match the values of this instance
        // returns true if they all match, false otherwise
        bool isSimilarTo(const CarInventory& car) const;
    };

    // check whether there are duplicate entries in the entire inventory
    // returns true if it finds two CarInventory objects that have similar information in the car array
    bool find_similar(CarInventory car[], const int num_cars);
}

#endif // ! SDDS_CARINVENTORY_H