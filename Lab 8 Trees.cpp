#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

struct Node
{
	string name;
	vector<Node *> child;
	Node *parent;
};

class Employee
{
private:
	Node *topEmployee;
public:
	Employee()
	{
		topEmployee = new Node();
	}
	~Employee() {}
	void firstEmployee(string employeeName, int employeeNumber)
	{
		createEmployee(topEmployee, employeeName, employeeNumber, topEmployee);
	}
	void createEmployee(Node *employeeNode, string employeeName, int employeeNumber, Node *parentNode)
	{
		string name;
		int number;
		employeeNode->name = employeeName;
		employeeNode->child.resize(employeeNumber);
		employeeNode->parent = parentNode;
		if (employeeNode->child.size() != 0)
		{
			for (int i = 0; i < employeeNode->child.size(); i++)
			{
				employeeNode->child[i] = new Node();
				cout << "The name of the employee " << i + 1 << " under the " << employeeNode->name << ": ";
				cin >> name;
				cout << "The number of employees working for " << name << ": ";
				cin >> number;
				createEmployee(employeeNode->child[i], name, number, employeeNode);
			}
		}
	}
	int countEmployee(Node *parent)
	{
		int count = 0;
		if (parent->child.size() != 0)
		{
			for (int i = 0; i < parent->child.size(); i++)
			{
				count = count + countEmployee(parent->child[i]);
			}
		}
		count = count + parent->child.size();
		return count;
	}
	void threeEmployee()
	{
		threeEmployee(topEmployee);
	}
	void threeEmployee(Node *parent)
	{
		int countThree = 0;
		if (parent->child.size() != 0)
		{
			countThree = countEmployee(parent);
			if (countThree > 3)
			{
				cout << parent->name << endl;
			}

			for (int i = 0; i < parent->child.size(); i++)
			{
				threeEmployee(parent->child[i]);
			}
		}
	}
	void zeroEmployee()
	{
		zeroEmployee(topEmployee);
	}
	void zeroEmployee(Node *parent)
	{
		int countZero = 0;
		Node *employee;
		employee = new Node();
		if (parent->child.size() != 0)
		{
			for (int i = 0; i < parent->child.size(); i++)
			{
				zeroEmployee(parent->child[i]);
			}
		}
		if (parent->child.size() == 0)
		{
			employee = parent;
			cout << employee->name;
			while (employee->parent != topEmployee)
			{
				employee = employee->parent;
				cout << ":" << employee->name;

			}
			cout << ":" << topEmployee->name << endl;
		}
	}
};

int main()
{
	Employee topEmployee;
	string employeeName;
	int employeeNumber;
	cout << "The name of the first employee: ";
	cin >> employeeName;
	cout << "The number of employees working for " << employeeName << ": ";
	cin >> employeeNumber;

	topEmployee.firstEmployee(employeeName, employeeNumber);

	cout << "The employees with 3+ employees: " << endl;
	topEmployee.threeEmployee();

	cout << "The employees without employee: " << endl;
	topEmployee.zeroEmployee();

	return 0;
}