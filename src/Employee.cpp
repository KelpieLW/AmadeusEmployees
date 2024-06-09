#include "Employee.h"
#include <string>

// Constructor
Employee::Employee(int id, const std::string& name, const std::string& department, double salary)
    : id(id), name(name), department(department), salary(salary) {}

// Getter for id
int Employee::getId() const {
    return id;
}

// Getter for name
const std::string& Employee::getName() const {
    return name;
}

// Getter for department
const std::string& Employee::getDepartment() const {
    return department;
}

// Getter for salary
double Employee::getSalary() const {
    return salary;
}