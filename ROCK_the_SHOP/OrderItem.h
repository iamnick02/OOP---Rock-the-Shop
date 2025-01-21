#ifndef ORDERITEM_H
#define ORDERITEM_H

#include <string>

using namespace std;

class OrderItem {
private:
    string productCode;
    int quantity;

public:
    OrderItem();
    OrderItem(const string& code, int qty);

    string getProductCode() const;
    void setProductCode(const string& code);
    int getQuantity() const;
    void setQuantity(int qty);
};

#endif
