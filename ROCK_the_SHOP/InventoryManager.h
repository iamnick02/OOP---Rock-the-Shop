#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include <vector>
#include <memory>
#include <algorithm>
#include "Product.h"

using namespace std;

class InventoryManager {
private:
    vector<shared_ptr<Product>> products;

public:
    InventoryManager();
    InventoryManager(vector<shared_ptr<Product>> initialProducts);
    void addProduct(const shared_ptr<Product>& product);
    void removeProduct(const string& uniqueCode);
    void updateStock(const string& uniqueCode, int newStock);
    shared_ptr<Product> getProduct(const string& uniqueCode) const;
    vector<shared_ptr<Product>> getAllProducts() const;
    bool checkStockValidity() const;
    bool productExists(const string& uniqueCode) const;
    void displayAllProducts() const;
};

#endif
