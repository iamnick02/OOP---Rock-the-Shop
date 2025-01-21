#include "Employee.h"

Employee::Employee()
    : id(0), firstName(""), lastName(""), CNP(""), hireDate(""), baseSalary(3500.0) {}

Employee::Employee(int id, string firstName, string lastName, string CNP, string hireDate)
    : id(id), firstName(firstName), lastName(lastName), CNP(CNP), hireDate(hireDate), baseSalary(3500.0) {
    if (!validateCNP(CNP)) {
        throw invalid_argument("Invalid CNP provided.");
    }
}

float Employee::calculateSalary(int years) const {
    return baseSalary + 100 * years;
}

void Employee::display() const {
    cout << "ID: " << id << "\nFirst Name: " << firstName << "\nLast Name: " << lastName
              << "\nCNP: " << CNP << "\nHire Date: " << hireDate << "\nSalary: " << calculateSalary(getYearsOfExperience()) << endl;
}

bool Employee::validateCNP(const string& CNP) {
    return CNP.length() == 13 && all_of(CNP.begin(), CNP.end(), ::isdigit);
}

bool Employee::isValidDate(const string& date) {
    if (date.length() != 10 || date[2] != '-' || date[5] != '-') {
        return false;
    }

    try {
        int day = stoi(date.substr(0, 2));
        int month = stoi(date.substr(3, 2));
        int year = stoi(date.substr(6, 4));

        if (year < 1900 || year > 2100 || month < 1 || month > 12 || day < 1 || day > 31) {
            return false;
        }

        tm timeStruct = {};
        timeStruct.tm_mday = day;
        timeStruct.tm_mon = month - 1;
        timeStruct.tm_year = year - 1900;

        return mktime(&timeStruct) != -1 &&
               timeStruct.tm_mday == day &&
               timeStruct.tm_mon == month - 1 &&
               timeStruct.tm_year == year - 1900;
    } catch (exception&) {
        return false;
    }
}

bool Employee::isBirthdayThisMonth() const {
    time_t t = time(nullptr);
    tm* timePtr = localtime(&t);
    int currentMonth = timePtr->tm_mon + 1;
    int birthMonth = stoi(CNP.substr(3, 2));
    return birthMonth == currentMonth;
}

void Employee::setFirstName(const string& firstName) {
    this->firstName = firstName;
}

void Employee::setLastName(const string& lastName) {
    this->lastName = lastName;
}

string Employee::getFirstName() const {
    return firstName;
}

string Employee::getLastName() const {
    return lastName;
}

string Employee::getCNP() const {
    return CNP;
}

int Employee::getId() const {
    return id;
}

string Employee::getHireDate() const {
    return hireDate;
}

float Employee::getBonusSalary() const{
    return baseSalary;
}

int Employee::getYearsOfExperience() const {
    time_t t = time(NULL);
    tm* timePtr = localtime(&t);

    int currentYear = 1900 + timePtr->tm_year;
    int hireYear = stoi(hireDate.substr(6, 4));

    return currentYear - hireYear;
}
