#ifndef SDDS_DISPLAYABLE_H_
#define SDDS_DISPLAYABLE_H_
#include <iostream>

namespace sdds {

    // base class

    class Displayable {

    public:

        // pure virtual function
        // does not need to be defined
        // must be overriden in a derived class
        virtual std::ostream& display(std::ostream& os)const = 0;

    };

    // overloaded insertion operator
    // simply calls the display function
    std::ostream& operator<<(std::ostream& os, const Displayable& D);
}

#endif // ! SDDS_DISPLAYABLE_H_