#ifndef EMPLOYEEMANAGER_H
#define EMPLOYEEMANAGER_H

#include "Employee.h"
#include "Manager.h"
#include "OperatorComenzi.h"
#include "Asistent.h"

using namespace std;

class EmployeeManager {
private:
    vector<shared_ptr<Employee>> employees;

public:
    EmployeeManager();
    EmployeeManager(vector<shared_ptr<Employee>> initialEmployees);
    void addEmployee(shared_ptr<Employee> employee);
    void removeEmployee(int id);
    void updateEmployeeInfo(int id, const string& newName);
    shared_ptr<Employee> getEmployee(int id) const;
    vector<shared_ptr<Employee>> getAllEmployees() const;
    bool checkOperationalStatus() const;
    void reportMostOrdersProcessed(const string& filename) const;
    void reportTop3MostValuableOrders(const string& filename) const;
    void reportTop3HighestSalaries(const string& filename) const;
};

#endif
