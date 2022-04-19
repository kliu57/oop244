#ifndef SDDS_STUDENT_H_
#define SDDS_STUDENT_H_

#include "Displayable.h"

namespace sdds{

    // derived class
    // derived from Displayable

    class Student : public Displayable {

        int m_stno{};           // student number, init to 0
        char m_name[41]{};      // 40 character name
        char m_subject[7]{};    // 6 character subject

        // private member function
        // sets student number, name, subject to argument values
        void set(int stno, const char* name, const char* subject);

    public:

        // constructor
        // safe empty state
        Student();

        // constructor
        // sets student number, name, subject to argument values
        Student(int stno, const char* name, const char* subject);

        // shadows base class function
        // prints student number, name, subject
        std::ostream& display(std::ostream& os) const;

        // overload equals to operator
        // returns true if this object has the same subject as argument Student
        // returns false otherwise
        bool operator==(const Student& S) const;
    };
}

#endif // ! SDDS_STUDENT_H_