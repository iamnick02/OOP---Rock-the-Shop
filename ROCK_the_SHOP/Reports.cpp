#include "Reports.h"

void Reports::generateReportMostOrdersProcessed(const EmployeeManager& manager, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Eroare la deschiderea fisierului: " << filename << endl;
        return;
    }

    auto employees = manager.getAllEmployees();
    vector<shared_ptr<OperatorComenzi>> operators;
    int maxOrders = 0;

    for (const auto& emp : employees) {
        auto op = dynamic_pointer_cast<OperatorComenzi>(emp);
        if (op) {
            operators.push_back(op);
            maxOrders = max(maxOrders, op->getCurrentOrderCount());
        }
    }

    file << "Nume,Prenume,Numar Comenzi\n";

    if (operators.empty()) {
        file << "Nu exista operatori in sistem.\n";
    } else {
        if (maxOrders == 0) {
            for (const auto& op : operators) {
                file << op->getFirstName() << "," << op->getLastName() << ",0\n";
            }
        } else {
            for (const auto& op : operators) {
                if (op->getCurrentOrderCount() == maxOrders) {
                    file << op->getFirstName() << "," << op->getLastName() << ","
                         << op->getCurrentOrderCount() << "\n";
                }
            }
        }
    }
    file.close();
}

void Reports::generateReportTop3MostValuableOrders(const EmployeeManager& manager, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Eroare la deschiderea fisierului: " << filename << endl;
        return;
    }

    auto employees = manager.getAllEmployees();
    vector<pair<float, shared_ptr<OperatorComenzi>>> employeeValues;

    for (const auto& emp : employees) {
        auto op = dynamic_pointer_cast<OperatorComenzi>(emp);
        if (op) {
            employeeValues.emplace_back(op->getTotalOrderValue(), op);
        }
    }

    sort(employeeValues.begin(), employeeValues.end(),
         [](const auto& a, const auto& b) { return a.first > b.first; });

    file << "Nume,Prenume,Valoare Totala Comenzi\n";
    for (size_t i = 0; i < 3 && i < employeeValues.size(); ++i) {
        file << employeeValues[i].second->getFirstName() << ","
             << employeeValues[i].second->getLastName() << ","
             << employeeValues[i].first << "\n";
    }
    file.close();
}

void Reports::generateReportTop3HighestSalaries(const EmployeeManager& manager, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Eroare la deschiderea fisierului: " << filename << endl;
        return;
    }

    auto employees = manager.getAllEmployees();
    vector<shared_ptr<Employee>> sortedEmployees = employees;

    sort(sortedEmployees.begin(), sortedEmployees.end(),
         [](const shared_ptr<Employee>& a, const shared_ptr<Employee>& b) {
             return a->calculateSalary(a->getYearsOfExperience()) >
                    b->calculateSalary(b->getYearsOfExperience());
         });

    file << "Nume,Prenume,Salariu\n";
    for (size_t i = 0; i < 3 && i < sortedEmployees.size(); ++i) {
        file << sortedEmployees[i]->getFirstName() << ","
             << sortedEmployees[i]->getLastName() << ","
             << sortedEmployees[i]->calculateSalary(sortedEmployees[i]->getYearsOfExperience()) << "\n";
    }
    file.close();
}
