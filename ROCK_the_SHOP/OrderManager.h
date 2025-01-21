#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include <queue>
#include <chrono>
#include <thread>
#include <atomic>
#include <fstream>
#include <iomanip>
#include "Order.h"
#include "OperatorComenzi.h"

class OrderManager {
private:
    vector<shared_ptr<OperatorComenzi>> operators;
    queue<shared_ptr<Order>> orderQueue;
    InventoryManager& inventory;
    atomic<bool> isSimulationRunning;
    unordered_map<int, chrono::steady_clock::time_point> orderStartTimes;

public:
    OrderManager(InventoryManager& inv);
    OrderManager(const vector<shared_ptr<OperatorComenzi>>& initialOperators, InventoryManager& inv);
    void addOperator(shared_ptr<OperatorComenzi> operatori);
    void assignOrder(const shared_ptr<Order>& order);
    void startSimulation();
    void stopSimulation();
    void processWaitingOrders();
    void distributeWorkLoad();
    string getCurrentTimestamp() const;
    void checkCompletedOrders();
    void displayOperatorStatus() const;
    void loadOrdersFromFile(const string& filename);
    vector<shared_ptr<OperatorComenzi>> getOperators() const;
};

#endif
