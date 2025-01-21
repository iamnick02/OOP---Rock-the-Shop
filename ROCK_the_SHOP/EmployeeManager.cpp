#include "EmployeeManager.h"
#include "Reports.h"

EmployeeManager::EmployeeManager() {}

EmployeeManager::EmployeeManager(vector<shared_ptr<Employee>> initialEmployees)
    : employees(initialEmployees) {
}

void EmployeeManager::addEmployee(shared_ptr<Employee> employee) {
    if (getEmployee(employee->getId()) != nullptr) {
        throw invalid_argument("Un angajat cu acest ID exista deja.");
    }

    time_t t = time(NULL);
    tm* timePtr = localtime(&t);

    int currentYear = 1900 + timePtr->tm_year;
    int birthYearLastTwoDigits = stoi(employee->getCNP().substr(1, 2));
    int century = (birthYearLastTwoDigits <= currentYear % 100) ? 2000 : 1900;
    int fullBirthYear = century + birthYearLastTwoDigits;

    if (currentYear - fullBirthYear >= 18) {
        employees.push_back(employee);
    } else {
        throw invalid_argument("Angajatul trebuie sa aibe cel putin varsta de 18 ani.");
    }
}

void EmployeeManager::removeEmployee(int id) {
    auto it = remove_if(employees.begin(), employees.end(),
                        [id](const shared_ptr<Employee>& emp) { return emp->getId() == id; });
    if (it != employees.end()) {
        employees.erase(it, employees.end());
        cout << "Angajatul cu ID " << id << " a fost sters.\n";
    } else {
        cout << "Angajatul cu ID " << id << " nu exista.\n";
    }
}

void EmployeeManager::updateEmployeeInfo(int id, const string& newName) {
    auto it = find_if(employees.begin(), employees.end(), [id](const shared_ptr<Employee>& emp) {
        return emp->getId() == id;
    });
    if (it != employees.end()) {
        (*it)->setFirstName(newName);
        cout << "Numele angajatului cu ID " << id << " a fost actualizat la " << newName << ".\n";
    } else {
        cout << "Angajatul cu ID " << id << " nu exista.\n";
    }
}


shared_ptr<Employee> EmployeeManager::getEmployee(int id) const {
    auto it = find_if(employees.begin(), employees.end(), [id](const shared_ptr<Employee>& emp) {
        return emp->getId() == id;
    });
    return (it != employees.end()) ? *it : nullptr;
}

vector<shared_ptr<Employee>> EmployeeManager::getAllEmployees() const {
    return employees;
}

bool EmployeeManager::checkOperationalStatus() const {
    int managerCount = 0, operatorCount = 0, assistantCount = 0;
    for (const auto& emp : employees) {
        if (dynamic_pointer_cast<Manager>(emp)) managerCount++;
        else if (dynamic_pointer_cast<OperatorComenzi>(emp)) operatorCount++;
        else if (dynamic_pointer_cast<Asistent>(emp)) assistantCount++;
    }

    if (managerCount < 1 || operatorCount < 3 || assistantCount < 1) {
        cout << "Magazinul nu poate functiona. Necesar: 1 manager, 3 operatori de comenzi, 1 asistent." << endl;
        cout << "Actual: " << managerCount << " manager(i), " << operatorCount << " operator(i) de comenzi, " << assistantCount << " asistent(i)." << endl;
        return false;
    }
    return true;
}

void EmployeeManager::reportMostOrdersProcessed(const string& filename) const {
    Reports::generateReportMostOrdersProcessed(*this, filename);
}

void EmployeeManager::reportTop3MostValuableOrders(const string& filename) const {
    Reports::generateReportTop3MostValuableOrders(*this, filename);
}

void EmployeeManager::reportTop3HighestSalaries(const string& filename) const {
    Reports::generateReportTop3HighestSalaries(*this, filename);
}

