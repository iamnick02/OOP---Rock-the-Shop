#include "OrderManager.h"

OrderManager::OrderManager(InventoryManager& inv)
    : inventory(inv), isSimulationRunning(false) {
}

OrderManager::OrderManager(const vector<shared_ptr<OperatorComenzi>>& initialOperators, InventoryManager& inv)
    : operators(initialOperators), inventory(inv), isSimulationRunning(false) {
}

void OrderManager::addOperator(shared_ptr<OperatorComenzi> operatori) {
    operators.push_back(operatori);
}

void OrderManager::assignOrder(const shared_ptr<Order>& order) {
    stringstream output;
    bool assigned = false;

    for (auto& op : operators) {
        if (op->getCurrentOrderCount() < 3) {
            op->assignOrder(order);
            orderStartTimes[order->getId()] = chrono::steady_clock::now();

            output << "[" << getCurrentTimestamp() << "] Comanda " << order->getId()
                  << " asignata operatorului " << op->getFirstName()
                  << " " << op->getLastName()
                  << " (Durata procesare: " << order->getProcessingDuration()
                  << " minute)\n";

            assigned = true;
            distributeWorkLoad();
            break;
        }
    }

    if (!assigned) {
        output << "[" << getCurrentTimestamp() << "] Toti operatorii sunt ocupati. "
               << "Comanda " << order->getId() << " a fost plasata in coada de asteptare.\n";
        orderQueue.push(order);
    }

    cout << output.str() << flush;
}

void OrderManager::startSimulation() {
    if (!isSimulationRunning) {
        isSimulationRunning = true;
        thread([this]() {
            while (isSimulationRunning) {
                checkCompletedOrders();
                this_thread::sleep_for(chrono::seconds(1));
            }
        }).detach();
    }
}

void OrderManager::stopSimulation() {
    isSimulationRunning = false;
}

void OrderManager::processWaitingOrders() {
    if (orderQueue.empty()) return;

    cout << "\n[" << getCurrentTimestamp() << "] Verificare comenzi in asteptare..." << endl;

    int initialQueueSize = orderQueue.size();
    int processedCount = 0;

    while (!orderQueue.empty()) {
        bool assigned = false;
        for (auto& op : operators) {
            if (op->getCurrentOrderCount() < 3) {
                auto order = orderQueue.front();
                orderQueue.pop();
                op->assignOrder(order);
                orderStartTimes[order->getId()] = chrono::steady_clock::now();
                cout << "[" << getCurrentTimestamp() << "] Comanda din asteptare "
                     << order->getId() << " asignata operatorului "
                     << op->getFirstName() << " " << op->getLastName()
                     << " (Durata procesare: " << order->getProcessingDuration()
                     << " minute)" << endl;
                assigned = true;
                processedCount++;
                break;
            }
        }
        if (!assigned) break;
    }

    distributeWorkLoad();

    if (processedCount > 0) {
        cout << "[" << getCurrentTimestamp() << "] " << processedCount
             << " comenzi din " << initialQueueSize
             << " au fost asignate operatorilor." << endl;
    }

    if (!orderQueue.empty()) {
        cout << "[" << getCurrentTimestamp() << "] " << orderQueue.size()
             << " comenzi raman in asteptare." << endl;
    }
}

void OrderManager::distributeWorkLoad() {
    bool changed = true;
    while (changed) {
        changed = false;
        sort(operators.begin(), operators.end(),
            [](const auto& a, const auto& b) {
                return a->getCurrentOrderCount() < b->getCurrentOrderCount();
            });

        if (operators.back()->getCurrentOrderCount() > operators.front()->getCurrentOrderCount() + 1) {
            auto order = operators.back()->popLastOrder();
            operators.front()->assignOrder(order);
            changed = true;
        }
    }
}

string OrderManager::getCurrentTimestamp() const {
    auto now = chrono::system_clock::now();
    auto time = chrono::system_clock::to_time_t(now);
    stringstream ss;
    ss << put_time(localtime(&time), "%d-%m-%Y %H:%M:%S");
    return ss.str();
}

void OrderManager::checkCompletedOrders() {
    auto currentTime = chrono::steady_clock::now();
    bool ordersCompleted = false;
    stringstream output;

    for (auto& op : operators) {
        auto orders = op->getAssignedOrders();
        vector<shared_ptr<Order>> remainingOrders;

        for (const auto& order : orders) {
            auto startIt = orderStartTimes.find(order->getId());
            if (startIt != orderStartTimes.end()) {
                auto elapsedMinutes = chrono::duration_cast<chrono::seconds>
                    (currentTime - startIt->second).count() / 60.0;

                if (elapsedMinutes >= order->getProcessingDuration()) {
                    output << "\n[" << getCurrentTimestamp() << "] Comanda " << order->getId()
                          << " finalizata de operatorul " << op->getFirstName()
                          << " " << op->getLastName() << "\n";

                    op->processOrder(order->getTotalPrice());
                    orderStartTimes.erase(startIt);
                    ordersCompleted = true;
                } else {
                    remainingOrders.push_back(order);
                }
            }
        }

        if (orders.size() != remainingOrders.size()) {
            op->clearOrders();
            for (const auto& order : remainingOrders) {
                op->assignOrder(order);
            }
        }
    }

    if (!output.str().empty()) {
        cout << output.str() << flush;
    }

    if (ordersCompleted) {
        processWaitingOrders();
    }
}

void OrderManager::displayOperatorStatus() const {
    stringstream output;
    output << "\n[" << getCurrentTimestamp() << "] Statusul operatorilor:\n\n";

    for (const auto& op : operators) {
        output << "Operator: " << op->getFirstName() << " " << op->getLastName() << "\n";
        auto orders = op->getAssignedOrders();
        if (!orders.empty()) {
            output << "Comenzi curente:\n";
            for (const auto& order : orders) {
                auto startIt = orderStartTimes.find(order->getId());
                if (startIt != orderStartTimes.end()) {
                    auto currentTime = chrono::steady_clock::now();
                    double elapsedMinutes =
                        chrono::duration_cast<chrono::seconds>(currentTime - startIt->second).count() / 60.0;

                    output << " - Comanda " << order->getId()
                           << " (Timpul scurs: " << fixed << setprecision(1)
                           << elapsedMinutes << "/" << order->getProcessingDuration()
                           << " minute)\n";
                }
            }
        } else {
            output << "Nicio comanda in procesare\n";
        }
        output << "\n";
    }

    if (!orderQueue.empty()) {
        output << "Comenzi in asteptare: " << orderQueue.size() << "\n";
    }
    output << "\n";

    cout << output.str();
}

void OrderManager::loadOrdersFromFile(const string& filename) {
    static bool isFirstLoad = true;

    if (!isFirstLoad) {
        cout << "\nToate comenzile au fost deja procesate.\n";
        return;
    }

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "\nEroare la deschiderea fisierului: " << filename << endl;
        return;
    }

    vector<string> orderLines;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            orderLines.push_back(line);
        }
    }
    file.close();

    cout << "\nInceperea procesarii comenzilor...\n\n";

    for (size_t i = 0; i < orderLines.size(); ++i) {
        const auto& line = orderLines[i];
        try {
            stringstream ss(line);
            string productCode;
            int quantity, duration;
            float totalPrice;
            string temp;

            if (!getline(ss, productCode, ',')) throw runtime_error("Cod produs invalid.");
            if (!getline(ss, temp, ',') || !(stringstream(temp) >> quantity)) throw runtime_error("Cantitate invalida.");
            if (!getline(ss, temp, ',') || !(stringstream(temp) >> duration)) throw runtime_error("Durata invalida.");
            if (!getline(ss, temp) || !(stringstream(temp) >> totalPrice)) throw runtime_error("Pret total invalid.");

            if (quantity <= 0) throw runtime_error("Cantitate invalida.");
            if (duration <= 0) throw runtime_error("Durata invalida.");
            if (totalPrice < 100) throw runtime_error("Pret total prea mic.");

            auto order = make_shared<Order>();
            order->addItem(OrderItem(productCode, quantity));
            order->setOrderDate(getCurrentTimestamp());
            order->setProcessingDuration(duration);
            order->setTotalPrice(totalPrice);

            if (order->validateOrder(inventory)) {
                assignOrder(order);
            } else {
                cout << "Comanda " << (i + 1) << " nu respecta restrictiile.\n";
            }

            this_thread::sleep_for(chrono::seconds(2));

        } catch (const exception& e) {
            cout << "\nEroare la procesarea comenzii " << (i + 1) << ": " << e.what() << endl;
        }
    }

    cout << "\nToate comenzile au fost citite din fisier.\n";
    isFirstLoad = false;
}


vector<shared_ptr<OperatorComenzi>> OrderManager::getOperators() const {
    return operators;
}
