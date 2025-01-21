#include "Product.h"

Product::Product() : name(""), stock(0), basePrice(0.0), uniqueCode("") {}

Product::Product(string name, int stock, float basePrice, string uniqueCode)
    : name(name), stock(stock), basePrice(basePrice), uniqueCode(uniqueCode) {}

string Product::getName() const {
    return name;
}

int Product::getStock() const {
    return stock;
}

float Product::getBasePrice() const {
    return basePrice;
}

string Product::getUniqueCode() const {
    return uniqueCode;
}

void Product::setStock(int newStock) {
    stock = newStock;
}

void Product::setName(string newName) {
    name = newName;
}

void Product::setBasePrice(float newBasePrice) {
    basePrice = newBasePrice;
}

void Product::setUniqueCode(string newUniqueCode) {
    uniqueCode = newUniqueCode;
}
