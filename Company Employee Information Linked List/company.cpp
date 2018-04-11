#pragma once
//Lab 8: Company Employee Information (Linked List)
//Contains Company class method definitions
//Vanesssa Mastrosimone
//CSC 2430
//March 12, 2018


#include <iostream>
#include <string>
using namespace std;
#include "company.h"
//#include "employee.h"
//#include "employeelist.h"

//Constructor for Company: default constructor
Company::Company()
{
}

//Adds an employee to the list
//Parameters specify the information about the employee;  creates a new Employee with the given data and inserts it into _list
//Returns true if it was able to add it, false otherwise
bool Company::AddEmployee(unsigned int id, const string& name, double salary, unsigned int managerID)
{
	Employee *worker = new Employee(id, name, salary, managerID);
	if (_list.Insert(worker))
		return true;
	else
		return false;
}


//Adds the specified employee to the list
//Creates a new Employee using the copy constructor and inserts it into _list; returns true if able to add it, false if not
bool Company::AddEmployee(const Employee& employee)
{
	Employee *worker = new Employee(employee);
	if (_list.Insert(worker))
		return true;
	else
		return false;
}


//Uses binary search to find an employee using ID given in parameter
//Returns -1 if the employee is not found; returns position of employee
int Company::FindById(unsigned int key)
{
	int position = BinarySearch(key);
	return position;
}

//Uses linear search starting from the position specified by the second parameter to find the first occurrence of given name in the array
//Returns -1 if employee is not found; returns position of employee
int Company::FindByName(const string& name, unsigned int position)
{
	for (int i = position; i < GetEmployeeCount(); i++)
	{
		if (name == Get(i)->GetName())
			return i;
	}
	return -1;
}

//Reads employee data from an istream into _list
//Returns the number of employees read
int Company::Read(istream& fin)
{
	bool failed = false;
	int numRead = 0;
	while (!fin.eof() && this != NULL)
	{
		Employee *worker = new Employee(0, "", 0.0, 0);
		if (!(worker->Read(fin)))
		{
			failed = true;
		}
		else
		{
			if (this->AddEmployee(*worker) == true)
				numRead++;
		}
		delete worker;
	}
	return numRead;
}

//Writes all employees in _list to the ostream
//Returns the number of employees written
int Company::Write(ostream& output)
{
	int numWritten = 0;
	for (int i = 0; i < GetEmployeeCount(); i++)
	{
		output << Get(i)->GetId() << " " << Get(i)->GetName() << " " << Get(i)->GetSalary() << " " << Get(i)->GetManagerId() << endl;
		numWritten++;
	}
	return numWritten;
}

//Returns the pointer of the Employee at the position specified by the parameter
//If the position is invalid, returns NULL
//The referenced object belongs to the object and should not be "deleted" by the client
Employee* Company::Get(unsigned int position)
{
	//If the position is invalid, returns NULL
	if (position >= GetEmployeeCount())
		return NULL;
	else
		return _list.Get(position);
}

//Returns the number of employees in _list
unsigned int Company::GetEmployeeCount()
{
	return _list.Size();
}


//Private: executes a binary search in the array; parameter incidates the key that is being searched
//Returns position found or -1 if not found
int Company::BinarySearch(int key)
{
	int first = 0, last = GetEmployeeCount() - 1;
	while (first <= last)
	{
		int mid = (first + last) / 2;
		if (key < Get(mid)->GetId())
			last = mid - 1;
		else if (key > Get(mid)->GetId())
			first = mid + 1;
		else //(key == Get(mid)->GetId())
			return mid;
	}
	return -1;

}

//Deletes the employee using the ID given in the parameter
//User of this method must be sure that it is a valid and existent ID, if not the method should return false
//Must validate that the employee to be erased does not have subordinates
//Returns false if they have subordinates; if they are allowed to be erased, return true and remove it from _list
bool Company::DeleteEmployee(unsigned int ID)
{
	int pos = FindById(ID);

	//Validate ID
	if (pos == -1)
		return false;

	else
	{
		//Validate that the employee to be erased is not a manager, return false if they have subordinates
		for (int i = 0; i < GetEmployeeCount(); i++)
		{
			//Employee has subordinates
			if (Get(i)->GetManagerId() == ID)
				return false;
		}

		_list.Remove(pos);

		//If they are able to be erased, free the allocated memory by that employee
		//delete Get(pos);

		//Decrement number of employees
		//HOW?

		return true;
	}
}


//Destructor, does not need to do anything
Company::~Company()
{
}