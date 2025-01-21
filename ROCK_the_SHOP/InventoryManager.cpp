#include "InventoryManager.h"

InventoryManager::InventoryManager() {}

InventoryManager::InventoryManager(vector<shared_ptr<Product>> initialProducts)
    : products(initialProducts) {
}

void InventoryManager::addProduct(const shared_ptr<Product>& product) {
    products.push_back(product);
}

void InventoryManager::removeProduct(const string& uniqueCode) {
    products.erase(remove_if(products.begin(), products.end(),
                             [&uniqueCode](const shared_ptr<Product>& product) {
                                return product->getUniqueCode() == uniqueCode;
                             }), products.end());
}

void InventoryManager::updateStock(const string& uniqueCode, int newStock) {
    auto it = find_if(products.begin(), products.end(),
                      [&uniqueCode](const shared_ptr<Product>& product) {
                          return product->getUniqueCode() == uniqueCode;
                      });
    if (it != products.end()) {
        (*it)->setStock(newStock);
    }
}

shared_ptr<Product> InventoryManager::getProduct(const string& uniqueCode) const {
    auto it = find_if(products.begin(), products.end(),
                      [&uniqueCode](const shared_ptr<Product>& product) {
                          return product->getUniqueCode() == uniqueCode;
                      });
    return (it != products.end()) ? *it : nullptr;
}

vector<shared_ptr<Product>> InventoryManager::getAllProducts() const {
    return products;
}

bool InventoryManager::checkStockValidity() const {
    unordered_map<string, int> productCounts;
    for (const auto& product : products) {
        string type = product->getType();
        productCounts[type]++;
    }

    if (productCounts["Clothing"] < 2 || productCounts["Disc"] < 2 || productCounts["VintageDisc"] < 2) {
        cout << "Stocul nu este suficient pentru functionarea magazinului." << endl;
        cout << "Necesar: Cel putin 2 produse din fiecare tip." << endl;
        cout << "Stoc actual: Articole vestimentare: " << productCounts["Clothing"]
             << ", Discuri: " << productCounts["Disc"]
             << ", Discuri vintage: " << productCounts["VintageDisc"] << endl;
        return false;
    }
    return true;
}

bool InventoryManager::productExists(const string& uniqueCode) const {
    return any_of(products.begin(), products.end(), [&uniqueCode](const shared_ptr<Product>& product) {
        return product->getUniqueCode() == uniqueCode;
    });
}

void InventoryManager::displayAllProducts() const {
    cout << "\nLista de produse disponibile:\n";
    for (const auto& product : products) {
        product->displayProductDetails();
        cout << "\n";
    }
}
