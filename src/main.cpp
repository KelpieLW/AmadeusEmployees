#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Employee.h"
#include <vector>
#include <algorithm>
#include "tinyxml2.h"
#include <filesystem>

namespace fs = std::filesystem;
using namespace tinyxml2; //Namespace to simplify the sintax 



//This function takes a file location of an employee XML file and then returns a list with an employee element containing all the employee information in its atributes
std::vector<Employee> xmlParseEmployees(const std::string &fileLocation) {
    std::vector<Employee> employees;
    XMLDocument doc;
    if (doc.LoadFile(fileLocation.c_str()) != XML_SUCCESS) {
        std::cerr << "Failed to load XML file." << std::endl;
        return employees;
    }
    

    int id;
    const std::string name;
    const std::string department;
    double salary;

    XMLElement* root = doc.FirstChildElement("employees");

    if (!root) {
        std::cerr << "Invalid XML format: 'employees' element not found." << std::endl;
        exit(EXIT_FAILURE); // Stop the program
    }
    
    for (XMLElement* elem = root->FirstChildElement("employee"); elem != nullptr; elem = elem->NextSiblingElement("employee")) {

        //Checks for a valid ID
        XMLElement* idElem = elem->FirstChildElement("id");
        //Checks for a valid name
        XMLElement* nameElem = elem->FirstChildElement("name");
        //Checks for a valid department
        XMLElement* deptElem = elem->FirstChildElement("department");
        //Checks for a valid salary
        XMLElement* salaryElem = elem->FirstChildElement("salary");

        //Check for missing pointers and require elements
        if (!idElem || !nameElem || !deptElem || !salaryElem) {
            std::cerr << "Invalid employee entry: Missing required elements." << std::endl;
            exit(EXIT_FAILURE); // Stop the program
        }
        //checks if the id is empty, id is a mandatory element
        const char* idText = idElem->GetText();
        if (!idText || std::string(idText).empty()) {
            std::cerr << "Error: Employee is missing a valid 'id' field." << std::endl;
            exit(EXIT_FAILURE); // Stop the program
        }
        
        // Check if salary element empty. Salary is a mandatory element
        const char* salaryText = salaryElem->GetText();
        if (!salaryText || std::string(salaryText).empty()) {
            std::cerr << "Error: Employee is missing a valid 'salary' field." << std::endl;
            exit(EXIT_FAILURE); // Stop the program
        }

        int id = std::stoi(idElem->GetText());
        const std::string name = nameElem->GetText();
        const std::string department = deptElem->GetText();
        double salary = std::stod(salaryElem->GetText());
        
        employees.emplace_back(id, name, department, salary);
    }

    return employees;
}

//Function to parse json structures
std::vector <Employee> jsonParserEmployees (const std::string& fileLocation){
    std::vector<Employee> employees;
    std::ifstream ifs(fileLocation);
    if (!ifs.is_open()) {
        std::cerr << "Could not open file: " << fileLocation << std::endl;
        return employees;
    }

    // Use IStreamWrapper to wrap the file stream
    rapidjson::IStreamWrapper isw(ifs);

    // Parse the JSON document
    rapidjson::Document doc;
    doc.ParseStream(isw);

    // Check for parsing errors
    if (doc.HasParseError()) {
        std::cerr << "Error  : " << doc.GetParseError() << "\n";
        std::cerr << "Offset : " << doc.GetErrorOffset() << "\n";
        return employees;
    }

    std::string name;
    int id = 0;
    std::string department;
    double salary = 0.0;
    const rapidjson::Value& jsonEmployees = doc["employees"];

    //Checks that the elements of the json are well formed. Id and Salary are mandatory fields, that's why the error ends the program
    for (rapidjson::SizeType i = 0; i < jsonEmployees.Size(); i++) {
        const rapidjson::Value& jsonEmployee = jsonEmployees[i];

        if (jsonEmployee.HasMember("name") && jsonEmployee["name"].IsString()) {            
            name=jsonEmployee["name"].GetString();
        }
        else {
            std::cerr << "Warning: Employee is missing a valid 'name' field.\n";
        }
        if (jsonEmployee.HasMember("id") && jsonEmployee["id"].IsInt()) {
            id = jsonEmployee["id"].GetInt();
        }
        else {
            std::cerr << "Error: Employee is missing a valid 'id' field.\n";
            exit(EXIT_FAILURE); // Stop the program
        }
        if (jsonEmployee.HasMember("department") && jsonEmployee["department"].IsString()) {
            department=jsonEmployee["department"].GetString();
        }
        else {
            std::cerr << "Warning: Employee is missing a valid 'department' field.\n";
        }
        if (jsonEmployee.HasMember("salary") && jsonEmployee["salary"].IsInt()) {
            salary=jsonEmployee["salary"].GetDouble();            
        }
        else {
            std::cerr << "Error: Employee is missing a valid 'salary' field.\n";
            exit(EXIT_FAILURE); // Stop the program
        }

        employees.emplace_back(id,name,department,salary);
    }
    
    return employees;
}
//Compare function of Id's used by the built in sorted function
bool idComparison (const Employee& employeeA, const Employee& employeeB) {
    return employeeA.getId() < employeeB.getId();
}

//This functions receives a list of employees and return the average salary
double averageSalary (std::vector<Employee>& employees){
    double average=0;
    for (Employee employeeValue : employees){
        average+=employeeValue.getSalary();        
    }
    average/=employees.size();
    return average;
}

//This function receives a list of employees and returns the highest salary
double highestSalary (std::vector<Employee>& employees){
    double maxSalary = std::numeric_limits<double>::min();
    for (int i = 0; i<employees.size();i++){
        if (employees[i].getSalary()>maxSalary){
            maxSalary=employees[i].getSalary();
        }
    }
    return maxSalary;
}
//Receives a list with employees and sorts it directly by id
void sortEmployeesById(std::vector<Employee>& unsortedEmployeeList){    
    std::sort(unsortedEmployeeList.begin(),unsortedEmployeeList.end(),idComparison);    
}
//Responsible for creating a new outputfile in the outputFiles folder. Contains the logic to format and write the output files with.
void outPutResults (std::vector <Employee> employeeList){
    fs::path projectDir = fs::path(__FILE__).parent_path();
        fs::path outputFileLocation = projectDir / ".." / "outputFiles" / "outputFile.txt";

        std::ofstream outFile(outputFileLocation);

        if (!outFile) {
            std::cerr << "Failed to open output file!" << std::endl;
            exit(EXIT_FAILURE); // Stop the program            
        }

        outFile << "Average Salary: " << averageSalary(employeeList) << "\n";
        outFile << "Highest Salary: " << highestSalary(employeeList) << "\n";

        sortEmployeesById(employeeList);
        outFile << "Sorted Employees by ID:\n";
        for (const Employee& employeeValue : employeeList) {
            
            outFile << "-------------------------------------\n";
            outFile << "ID: " << employeeValue.getId() << "\n";
            outFile << "Name: " << employeeValue.getName() << "\n";
            outFile << "Department: " << employeeValue.getDepartment() << "\n";
            outFile << "Salary: " << employeeValue.getSalary() << "\n";
            
        }

        outFile.close();
}

int main(){
    
    std::string fileLocation;
    std::cout << "Please enter your employees file location and name.\nThis program works with both XML and JSON files.\n";
    
    std::cin >> fileLocation; 
    
    std::vector <Employee> employeeList;
    

    if (fileLocation.find(".xml")!= std::string::npos){

        employeeList=xmlParseEmployees(fileLocation);        
    }

    else if(fileLocation.find(".json")!= std::string::npos){          

        employeeList = jsonParserEmployees(fileLocation);        

    }
    
    else {
        std::cout <<"Unsuported file type";
        exit(EXIT_FAILURE); // Stop the program   
    }
    outPutResults(employeeList);
    return 0;
}