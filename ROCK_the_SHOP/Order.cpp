#include "Order.h"

int Order::nextId = 1;

Order::Order(): id(nextId++), totalPrice(0.0), items(), isProcessed(false), processingDuration(0)
{
    time_t now = time(0);
    orderDate = ctime(&now);
}

Order::Order(const vector<OrderItem>& items, const string& date, int duration)
    : id(nextId++), totalPrice(0.0), items(items), orderDate(date), isProcessed(false), processingDuration(duration) {}

void Order::addItem(const OrderItem& item)
{
    items.push_back(item);
}

void Order::calculateTotalPrice(const InventoryManager& inventory)
{
    totalPrice = 0.0;
    for (const auto& item : items)
    {
        auto product = inventory.getProduct(item.getProductCode());
        if (product)
        {
            totalPrice += product->calculateDeliveryPrice() * item.getQuantity();
        }
    }
}

bool Order::processOrder(InventoryManager& inventory, vector<shared_ptr<Employee>>& employees)
{
    if (validateOrder(inventory))
    {
        isProcessed = true;
        return true;
    }
    return false;
}

void Order::displayOrderDetails() const
{
    cout << "Order Date: " << orderDate << "\nTotal Price: " << totalPrice << "\nProcessing Duration: " << processingDuration << " minutes" << endl;
    for (const auto& item : items)
    {
        cout << "Product Code: " << item.getProductCode() << ", Quantity: " << item.getQuantity() << endl;
    }
}

bool Order::validateOrder(const InventoryManager& inventory) const {
    int discCount = 0, clothingCount = 0;
    float basePriceTotal = 0.0;

    for (const auto& item : items) {
        auto product = inventory.getProduct(item.getProductCode());
        if (!product) {
            cout << "Produsul " << item.getProductCode() << " nu exista in stoc.\n";
            return false;
        }

        int quantity = item.getQuantity();
        basePriceTotal += product->getBasePrice() * quantity;

        if (auto discPtr = dynamic_pointer_cast<Disc>(product)) {
            discCount += quantity;
            if (discCount > 5) {
                cout << "Prea multe discuri in comanda: " << discCount << " (max 5)\n";
                return false;
            }
        } else if (auto clothingPtr = dynamic_pointer_cast<Clothing>(product)) {
            clothingCount += quantity;
            if (clothingCount > 3) {
                cout << "Prea multe articole vestimentare in comanda: " << clothingCount << " (max 3)\n";
                return false;
            }
        }
    }

    if (basePriceTotal < 100) {
        cout << "Valoarea comenzii (" << basePriceTotal << " RON) este sub minimul de 100 RON\n";
        return false;
    }

    return true;
}


float Order::getTotalPrice() const
{
    return totalPrice;
}

int Order::getProcessingDuration() const
{
    return processingDuration;
}

string Order::getOrderDate() const
{
    return orderDate;
}

void Order::setOrderDate(const string& date)
{
    orderDate = date;
}

void Order::setProcessingDuration(int duration)
{
    processingDuration = duration;
}

void Order::setTotalPrice(float price)
{
    totalPrice = price;
}

int Order::getId() const
{
    return id;
}

void Order::setId(int newId)
{
    id = newId;
}

void Order::setIsProcessed(bool processed) {
    isProcessed = processed;
}
