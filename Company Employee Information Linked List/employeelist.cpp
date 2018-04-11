//Lab 8: Company Employee Information (Linked List)
//Contains EmployeeList class method definitions
//Vanesssa Mastrosimone
//CSC 2430
//March 12, 2018


#include <iostream>
#include <string>
using namespace std;
//#include "company.h"
//#include "employee.h"
#include "employeelist.h"

//Private: uses delete to free up every node in the list
//When a node is freed up, the Employee object it points to is also freed
void EmployeeList::DestroyList()
{
	Node *current = _head;
	while (current != NULL)
	{
		Node *temp = current;
		current = current->next;
		delete temp->data;
		temp->data = NULL;
		delete temp;
	}
}

//Constructor: initializes _head to NULL and _size to 0
EmployeeList::EmployeeList()
{
	_head = NULL;
	_size = 0;
}

//Inserts this pointer to an Employee object into the correct position in the list so it remains sorted by ID
//Allocates a node to store this pointer to an Employee object
//Node is linked into the list, _size is updated, returns true
bool EmployeeList::Insert(Employee* ptr)
{

	//List is currently empty
	if (_head == NULL)
	{
		Node *n = new Node();
		n->data = ptr;
		_head = n;
		_size++;
		return true;
	}

	//Insert at start of list
	else if (ptr->GetId() < _head->data->GetId())
	{
		Node *n = new Node();
		n->data = ptr;
		_head->prev = n;
		n->next = _head;
		n->prev = NULL;
		_head = n;
		_size++;
		return true;
	}

	else
	{
		//Insert at middle or end of list
		Node *temp = _head;
		Node *trailer = _head;
		int tempID = temp->data->GetId();
		int currentID = ptr->GetId();
		while (temp != NULL && tempID < currentID)
		{
			trailer = temp;
			temp = temp->next;
			if (temp != NULL)
				tempID = temp->data->GetId();

		}
		Node *n = new Node();
		n->data = ptr;
		trailer->next = n;
		n->next = temp;
		n->prev = trailer;
		if (temp != NULL)
			temp->prev = n;
		_size++;
		return true;
	}
}

//Returns a pointer to the Employee object stored at the position given by the parameter
//If the position is invalid, returns NULL
//Referenced object belongs to the object and should not be "deleted" by the client
Employee* EmployeeList::Get(unsigned int position)
{
	Node *temp = _head;
	for (int i = 0; i < position && temp != NULL; i++)
	{
		/*if (temp->next != NULL)*/
			temp = temp->next;
	}

	//Position is invalid
	if (temp == NULL)
		return NULL;

	else
		return temp->data;

}

//Searches the list for a node storing a pointer to an Employee object that is "Equal" to the Employee object specified as a parameter
//Uses the "Equals" method of the Employee object for comparison
//If the node is found, position returned. Otherwise, returns -1
int EmployeeList::IndexOf(const Employee& worker) 
{
	Node *current = _head;
	int pos = 0;

	while (current != NULL)
	{
		if (Get(pos)->Equals(worker))
			return pos;
		current = current->next;
		pos++;
	}
		return -1;
}

//Removes the node from the list at the position specified by the parameter
//If the position is invalid, returns false
//Otherwise, the node is unlinked from the list, and the node and the Employee object that it points are both deallocated, _size updated, returns true
bool EmployeeList::Remove(unsigned int position)
{
	//Empty list
	if (_head == NULL)
		return false;

	//First element
	if (position == 0)
	{
		if (_head->next == NULL)
		{
			delete _head->data;
			delete _head;
			_head = NULL;
			_size--;
		}
		else
		{
			Node *tempHead = _head;
			_head = _head->next;
			delete tempHead->data;
			delete tempHead;
			_size--;
		}
		return true;
	}

	Node *temp = _head;
	Node *follow = temp;
	for (int i = 0; temp != NULL && i < position; i++)
	{
		follow = temp;
		temp = temp->next;
	}

	//Position is invalid
	if (temp == NULL)
	{
		return false;
	}

	follow->next = temp->next;
	if (temp->next != NULL)
		temp->next->prev = follow;
	delete temp->data;
	delete temp;
	_size--;
	return true;
}

//Writes all the available employees to the ostream
//Returns the number of employees written
int EmployeeList::Write(ostream& output) 
{
	int numWritten = 0;
	for (int i = 0; i < Size() - 1; i++)
	{
		output << Get(i)->ToString();
		numWritten++;
	}
	return numWritten;
}

//Reads an istream and extracts all the employees data from there
//As each employee is read, an Employee object is allocated and inserted in the appropriate place in the list according to the sort order
//Returns the number of employees read
int EmployeeList::Read(istream& fin)
{
	int numRead = 0;
	while (!fin.eof())
	{
		Employee *worker = new Employee(0, "", 0.0, 0);
		if (worker->Read(fin))
		{
			Insert(worker);
			numRead++;
		}
		
	}

	return numRead;
}

//Returns true if there are no nodes in the list, false otherwise
bool EmployeeList::IsEmpty() 
{
	if (Size() == 0)
		return true;
	else
		return false;
}

//Returns the number of nodes in the list
unsigned int EmployeeList::Size() 
{
	return _size;
}

//Destructor: calls DestroyList to free up all allocated memory stored in the list
EmployeeList::~EmployeeList()
{
	DestroyList();
}