#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <ctime>

using namespace std;

class Employee {
protected:
    int id;
    string firstName;
    string lastName;
    string CNP;
    string hireDate;
    float baseSalary = 3500.0;

public:
    Employee();
    Employee(int id, string firstName, string lastName, string CNP, string hireDate);
    virtual ~Employee() {}
    virtual float calculateSalary(int years) const;
    virtual void display() const;
    virtual string getRole() const = 0;
    bool isBirthdayThisMonth() const;
    static bool validateCNP(const string& CNP);
    static bool isValidDate(const string& date);

    void setFirstName(const string& firstName);
    void setLastName(const string& lastName);
    string getFirstName() const;
    string getLastName() const;
    string getCNP() const;
    string getHireDate() const;
    float getBonusSalary() const;
    int getId() const;
    int getYearsOfExperience() const;
};

#endif
