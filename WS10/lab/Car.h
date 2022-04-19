#ifndef SDDS_CAR_H_
#define SDDS_CAR_H_

#include "Displayable.h"

namespace sdds{

    // derived class
    // derived from Displayable

    class Car : public Displayable {

        char m_plate[9]{};      // 8 character license plate
        char m_make[41]{};      // 40 character car make
        char m_model[41]{};     // 40 character car model

        // private member function
        // sets the plate, make and model to argument values
        void set(const char* plate, const char* make, const char* model);

    public:

        // contructor
        // plate, make and model are nullptr
        Car();

        // constructor
        // plate, make and model are set to argument values
        Car(const char* plate, const char* make, const char* model);

        // shadows base class function
        // prints plate, make, model
        std::ostream& display(std::ostream& os)const;

        // overload equals to operator
        // returns true if this object has the same make as argument Car
        // returns false otherwise
        bool operator==(const Car& C)const;
    };
}

#endif // ! SDDS_CAR_H_