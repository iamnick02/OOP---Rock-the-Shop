#include "Asistent.h"

Asistent::Asistent() : Employee(0, "", "", "", "") {}

Asistent::Asistent(int id, string firstName, string lastName, string CNP, string hireDate)
    : Employee(id, firstName, lastName, CNP, hireDate) {}

float Asistent::calculateSalary(int years) const {
    float salary = baseSalary + 100 * years;
    salary *= 0.75;
    if (isBirthdayThisMonth()) {
        salary += 100;
    }
    return salary;
}

string Asistent::getRole() const {
    return "Asistent";
}
