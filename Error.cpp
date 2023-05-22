#include "Error.h"
#include <iostream>
#include <cstdlib>

void fatalError(std::string errorMessage)
{
	std::cout << "Error:: " + errorMessage + "\n";
	std::cin.get();
	exit(EXIT_FAILURE);
}
