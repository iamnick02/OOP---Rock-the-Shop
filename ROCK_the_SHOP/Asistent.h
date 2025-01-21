#ifndef ASISTENT_H
#define ASISTENT_H

#include "Employee.h"

class Asistent : public Employee {
public:
    Asistent();
    Asistent(int id, string firstName, string lastName, string CNP, string hireDate);
    float calculateSalary(int years) const override;
    string getRole() const;
};

#endif
