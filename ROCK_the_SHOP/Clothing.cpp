#include "Clothing.h"

Clothing::Clothing() : Product(), color(""), brand("") {}

Clothing::Clothing(string name, int stock, float basePrice, string uniqueCode, string color, string brand)
    : Product(name, stock, basePrice, uniqueCode), color(color), brand(brand) {}

float Clothing::calculateDeliveryPrice() const
{
    return getBasePrice() + 20;
}

string Clothing::getColor() const
{
    return color;
}

string Clothing::getBrand() const
{
    return brand;
}

string Clothing::getType() const
{
    return "Clothing";
}

void Clothing::displayProductDetails() const {
    cout << "Articol Vestimentar: " << getName() << " (Cod: " << getUniqueCode() << ")"
         << "\nStoc: " << getStock() << ", Pret de baza: " << getBasePrice() << " RON"
         << ", Pret final (cu livrare): " << calculateDeliveryPrice() << " RON"
         << "\nCuloare: " << getColor() << ", Brand: " << getBrand() << "\n";
}

