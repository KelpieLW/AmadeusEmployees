# AmadeusEmployees

## Introduction

This C++ project was made with CMake using MSYS2 compilers.

> gcc (Rev3, Built by MSYS2 project) 13.2.0
> g++ (Rev3, Built by MSYS2 project) 13.2.

AmadeusEmployees is a command line tool that receives employee data given in **XML** and **JSON** and performs three key functions over it:

1. It generates the average salary of all the employees given in the data files.
2. Shows the details of the employee with the highest salary.
3. Sorts the list of employees by ID in ascending order.

The data is taken by the tool and manipulated resulting in an output file that will be located inside the folder **outputFiles** on the root of the project. This file will contain the information mentioned above and will be available in a simpler txt. file.

## Employees

An employee is defined by the following atributes:

- Id - _Mandatory Field_
- Name
- Department
- Salary - _Mandatory Field_

**Employee example:**
Id: 15
Name: Brandon Smith
Department: Support
Salary: 1000000

An employee has the mandatory fields described above. Introducing XML or JSON files missing one of these mandatory fields will result in an error.

## Execution

A Bash Script was made to use the building routines of CMaker and generate the executable of the project the script can be run with the following command:

> Bash BuildAndRun.sh

After a succesful building process the executable will be available inside the **build** folder located at the root of the project. Under the name of AmadeusEmployee.exe. Executing it will bring the command prompt. A message will ask you for the exact location of the input file, remember that a valid file must be in XML or JSON format, every element on the data structure must contain the mandatory fields mentioned above. Here is an example of a valid path:

> C:\Users\user\Downloads\Amadeus\AmadeusEmployees\inputFiles\employee.json

This project contains a folder of example input files for testing purposes called **inputFiles**. This folder contains example of incorrect XML and JSON files.
