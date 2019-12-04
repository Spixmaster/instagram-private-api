#include "ig/SpecialTools.h"
#include <iostream>

int main()
{
	std::string temp = ig::SpecialTools::md5_hash("abc1234");

	std::cout << temp << std::endl;

	return 0;
}
