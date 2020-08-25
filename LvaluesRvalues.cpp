#include <iostream>

void PrintName(const std::string& name)
{
	std::cout << name << std::endl;
}

void PrintName2(const std::string& name)
{
	std::cout << "[lvalue]" << name << std::endl;
}

void PrintName2(std::string&& name)
{
	std::cout << "[rvalue]" << name << std::endl;
}

int main()
{
	std::string firstName = "Charlie";
	std::string lastName = "Brown";
	std::string fullName = firstName + " " + lastName;

	PrintName(fullName);
	PrintName(firstName + " " + lastName); // needs PrintName argument to be const (otherwise it complains: the initial value of reference to non-const must be an lvalue)

	PrintName2(fullName);					// [lvalue]Charlie Brown
	PrintName2(firstName + " " + lastName); // [rvalue]Charlie Brown
}