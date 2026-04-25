#include "whatever.hpp"
#include <iostream>
#include <string>

int main()
{
	std::string	str1 = "hello";
	std::string str2 = "world";

	std::cout << str1 << " " << str2 << std::endl;
	swap(str1, str2);
	std::cout << str1 << " " << str2 << std::endl;

	int n1 = 42;
	int n2 = 24;
	std::cout << n1 << " " << n2 << std::endl;
	swap(n1, n2);
	std::cout << n1 << " " << n2 << std::endl;

}