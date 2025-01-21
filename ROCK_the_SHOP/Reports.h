#ifndef REPORTS_H
#define REPORTS_H

#include "EmployeeManager.h"
#include <fstream>

class Reports {
public:
    static void generateReportMostOrdersProcessed(const EmployeeManager& manager, const string& filename);
    static void generateReportTop3MostValuableOrders(const EmployeeManager& manager, const string& filename);
    static void generateReportTop3HighestSalaries(const EmployeeManager& manager, const string& filename);
};

#endif
