#include "Lexer.hpp"

int main(int ac, char const **av)
{
    std::vector<CodeLine> code;

	Lexer lexer;
	try {
		lexer.handle(ac, av, code);
		if (lexer.errors > 0) {
			std::string msg = "Total \e[31;1merrors\e[0m after lexer phase : " + std::to_string(lexer.errors) + "\n";
			std::cout << msg << std::endl;
			for (auto line : code)
				line.printError();
			std::cout << std::endl;
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}