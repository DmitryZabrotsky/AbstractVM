#include "Lexer.hpp"

int main(int ac, char const **av)
{
    std::vector<CodeLine> code;

	Lexer lexer;
	try {
		lexer.handle(ac, av);
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}