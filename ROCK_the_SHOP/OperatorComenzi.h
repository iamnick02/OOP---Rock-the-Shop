#ifndef OPERATORCOMENZI_H
#define OPERATORCOMENZI_H

#include "Employee.h"
#include "Order.h"

class OperatorComenzi : public Employee
{
private:
    float salesBonus;
    vector<shared_ptr<Order>> assignedOrders;
    int processedOrderCount = 0;

public:
    OperatorComenzi();
    OperatorComenzi(int id, string firstName, string lastName, string CNP, string hireDate);
    void processOrder(float orderValue);
    float calculateSalary(int years) const override;
    string getRole() const;
    float getSalesBonus() const;
    void assignOrder(const shared_ptr<Order>& order);
    int getCurrentOrderCount() const;
    shared_ptr<Order> popLastOrder();
    vector<shared_ptr<Order>> getAssignedOrders() const;
    float getTotalOrderValue() const;
    void clearOrders();
    int getProcessedOrderCount() const;

};

#endif
