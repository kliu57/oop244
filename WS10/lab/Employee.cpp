#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <cstring>
#include "Employee.h"

namespace sdds{

    // private member function
    void Employee::set(int stno, const char* name, int officeNo){
        m_empno = stno;
        std::strcpy(m_name, name);
        m_officeNo = officeNo;
    }

    // constructor
    Employee::Employee() {
    }

    // constructor
    Employee::Employee(int stno, const char* name , int officeNo){
        set(stno, name, officeNo);
    }

    std::ostream& Employee::display(std::ostream& os)const{
        return os << m_empno << ", " << m_name << ", " << m_officeNo;
    }

    bool Employee::operator==(const Employee& E)const{
        return m_officeNo == E.m_officeNo;
    }
}

