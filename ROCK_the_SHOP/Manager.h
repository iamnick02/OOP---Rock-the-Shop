#ifndef MANAGER_H
#define MANAGER_H

#include "Employee.h"

class Manager : public Employee {
public:
    Manager();
    Manager(int id, string firstName, string lastName, string CNP, string hireDate);
    float calculateSalary(int years) const override;
    string getRole() const;
};

#endif
