#include "OrderItem.h"

OrderItem::OrderItem() : productCode(""), quantity(0) {}

OrderItem::OrderItem(const string& code, int qty) : productCode(code), quantity(qty) {}

string OrderItem::getProductCode() const {
    return productCode;
}

void OrderItem::setProductCode(const string& code) {
    productCode = code;
}

int OrderItem::getQuantity() const {
    return quantity;
}

void OrderItem::setQuantity(int qty) {
    quantity = qty;
}

