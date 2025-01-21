#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class Product {
protected:
    string name;
    int stock;
    float basePrice;
    string uniqueCode;

public:
    Product();
    Product(string name, int stock, float basePrice, string uniqueCode);
    virtual ~Product() {}
    virtual float calculateDeliveryPrice() const = 0;
    virtual void displayProductDetails() const = 0;

    string getName() const;
    int getStock() const;
    float getBasePrice() const;
    string getUniqueCode() const;
    virtual string getType() const = 0;
    void setStock(int newStock);
    void setName(string newName);
    void setBasePrice(float newBasePrice);
    void setUniqueCode(string newUniqueCode);
};

#endif

