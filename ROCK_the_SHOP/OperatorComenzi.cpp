#include "OperatorComenzi.h"

OperatorComenzi::OperatorComenzi() : Employee(0, "", "", "", "") {}

OperatorComenzi::OperatorComenzi(int id, string firstName, string lastName, string CNP, string hireDate)
    : Employee(id, firstName, lastName, CNP, hireDate), salesBonus(0.0) {}

void OperatorComenzi::processOrder(float orderValue)
{
    salesBonus += orderValue * 0.005;
}

float OperatorComenzi::calculateSalary(int years) const
{
    float salary = baseSalary + 100 * years + salesBonus;
    if (isBirthdayThisMonth())
    {
        salary += 100;
    }
    return salary;
}

string OperatorComenzi::getRole() const
{
    return "Operator Comenzi";
}

float OperatorComenzi::getSalesBonus() const
{
    return salesBonus;
}

void OperatorComenzi::assignOrder(const shared_ptr<Order>& order)
{
    assignedOrders.push_back(order);
}

int OperatorComenzi::getCurrentOrderCount() const
{
    return assignedOrders.size();
}

shared_ptr<Order> OperatorComenzi::popLastOrder()
{
    if (!assignedOrders.empty())
    {
        auto order = assignedOrders.back();
        assignedOrders.pop_back();
        return order;
    }
    return nullptr;
}

vector<shared_ptr<Order>> OperatorComenzi::getAssignedOrders() const
{
    return assignedOrders;
}

float OperatorComenzi::getTotalOrderValue() const
{
    float total = 0;
    for (auto& order : assignedOrders)
    {
        total += order->getTotalPrice();
    }
    return total;
}

void OperatorComenzi::clearOrders()
{
    assignedOrders.clear();
}

int OperatorComenzi::getProcessedOrderCount() const
{
    return processedOrderCount;
}
