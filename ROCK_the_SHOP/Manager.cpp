#include "Manager.h"

Manager::Manager() : Employee(0, "", "", "", "") {}

Manager::Manager(int id, string firstName, string lastName, string CNP, string hireDate)
    : Employee(id, firstName, lastName, CNP, hireDate) {}

float Manager::calculateSalary(int years) const {
    return (baseSalary + 100 * years) * 1.25;
}

string Manager::getRole() const {
    return "Manager";
}
