#ifndef SDDS_EMPLOYEE_H_
#define SDDS_EMPLOYEE_H_

#include "Displayable.h"

namespace sdds{

    // derived class
    // derived from Displayable

    class Employee : public Displayable {

    int m_empno{};          // employee number, init to value 0
    char m_name[41]{};      // 40 character name
    int m_officeNo{};       // office number, init to value 0

    void set(int empno, const char* name, int officNo);

    public:
        // constructor
        // safe empty state
        Employee();

        // constructor
        // emp number, name, office number set to argument values
        Employee(int empno, const char* name, int officNo);

        // shadows base class function
        // prints emp number, name, office number
        std::ostream& display(std::ostream& os)const;

        // overload equals to operator
        // returns true if this object has the same office number as argument Employee
        // returns false otherwise
        bool operator==(const Employee& E)const;
    };
}
#endif // ! SDDS_EMPLOYEE_H_