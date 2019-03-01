#include <iostream>
#include "Parser.hpp"

int main(int ac, char const **av)
{
	Parser parser;
	try {
		parser.parse(ac, av);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}