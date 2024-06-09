#include "Employee.h"
#include <string>

// Constructor
Employee::Employee(int id, const std::string& name, const std::string& department, double salary)
    : id(id), name(name), department(department), salary(salary) {}

// Getter and setter for id
void Employee::setId(int id) {
    this->id = id;
}
int Employee::getId() const {
    return id;
}

// Getter and setter for name
void Employee::setName(const std::string& name) {
    this->name = name;
}
const std::string& Employee::getName() const {
    return name;
}

// Getter and setter for department
void Employee::setDepartment(const std::string& department) {
    this->department = department;
}
const std::string& Employee::getDepartment() const {
    return department;
}

// Getter and setter for salary
void Employee::setSalary(double salary) {
    this->salary = salary;
}
double Employee::getSalary() const {
    return salary;
}