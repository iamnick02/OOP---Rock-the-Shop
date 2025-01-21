#ifndef CLOTHING_H
#define CLOTHING_H

#include "Product.h"

using namespace std;

class Clothing : public Product {
private:
    string color;
    string brand;

public:
    Clothing();
    Clothing(string name, int stock, float basePrice, string uniqueCode, string color, string brand);
    float calculateDeliveryPrice() const override;

    string getColor() const;
    string getBrand() const;
    string getType() const;
    void displayProductDetails() const override;
};

#endif

