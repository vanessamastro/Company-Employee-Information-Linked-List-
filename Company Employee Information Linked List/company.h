#pragma once
//Lab 8: Company Employee Information (Linked List)
//Contains Company class declaration
//Vanesssa Mastrosimone
//CSC 2430
//March 12, 2018


#include <iostream>
#include <string>
using namespace std;
#include "employeelist.h"
#include "employee.h"

class Company
{
private:
	//Stores and manages the list of employees; Company class will be a client of this class
	EmployeeList _list;
	int BinarySearch(int);
public:
	//Default constructor
	Company();

	bool AddEmployee(unsigned int, const string&, double, unsigned int = 0);
	bool AddEmployee(const Employee&);
	bool DeleteEmployee(unsigned int);

	int FindById(unsigned int);
	int FindByName(const string&, unsigned int = 0);

	int Read(istream&);
	int Write(ostream&);

	Employee* Get(unsigned int);
	unsigned int GetEmployeeCount();

	//Destructor, does nothing
	~Company();
};