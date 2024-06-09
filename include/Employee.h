#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

class Employee {
public:
    Employee(int id, const std::string& name, const std::string& department, double salary);

    void setId(int id);
    int getId() const;

    void setName(const std::string& name);
    const std::string& getName() const;

    void setDepartment(const std::string& department);
    const std::string& getDepartment() const;

    void setSalary(double salary);
    double getSalary() const;

private:
    int id;
    std::string name;
    std::string department;
    double salary;
};

#endif // EMPLOYEE_H