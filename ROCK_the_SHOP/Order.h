#ifndef ORDER_H
#define ORDER_H

#include "InventoryManager.h"
#include "Employee.h"
#include "Clothing.h"
#include "Disc.h"
#include "VintageDisc.h"
#include "OrderItem.h"

using namespace std;

class Order {
private:
    int id;
    float totalPrice;
    vector<OrderItem> items;
    string orderDate;
    bool isProcessed;
    int processingDuration;
    static int nextId;

public:
    Order();
    Order(const vector<OrderItem>& items, const string& date, int duration);

    void addItem(const OrderItem& item);
    void calculateTotalPrice(const InventoryManager& inventory);
    bool processOrder(InventoryManager& inventory, vector<shared_ptr<Employee>>& employees);
    void displayOrderDetails() const;
    bool validateOrder(const InventoryManager& inventory) const;

    float getTotalPrice() const;
    int getProcessingDuration() const;
    string getOrderDate() const;
    void setOrderDate(const string& date);
    void setProcessingDuration(int duration);
    void setTotalPrice(float price);
    int getId() const;
    void setId(int newId);
    void setIsProcessed(bool processed);
};

#endif
