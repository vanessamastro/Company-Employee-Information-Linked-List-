#pragma once
//Lab 8: Company Employee Information (Linked List)
//Contains EmployeeList class declaration
//Vanesssa Mastrosimone
//CSC 2430
//March 12, 2018


#include <iostream>
#include <string>
using namespace std;

#include "employee.h"


class EmployeeList
{
private:
	struct Node {
		Employee *data;
		Node *next;
		Node *prev;
	};
	Node* _head;
	unsigned int _size;	//Number of nodes in the list

	void DestroyList();

public:
	//Constructor
	EmployeeList();

	bool Insert(Employee*);
	Employee* Get(unsigned int);
	int IndexOf(const Employee&);
	bool Remove(unsigned int);
	
	int Write(ostream&);
	int Read(istream&);

	bool IsEmpty();
	unsigned int Size();

	//Destructor
	~EmployeeList();
};
