#include "../incl/Parser.hpp"

int main(int ac, char const **av)
{
    code_t code;

	Lexer lexer;
	Parser parser;
	try {
		lexer.handle(ac, av, code);
		if (lexer.errors > 0) {
			std::string msg = "Total \e[31;1merrors\e[0m after lexer phase : " + std::to_string(lexer.errors) + "\n";
			std::cout << msg << std::endl;
			for (auto line : code)
				line.printError();
			std::cout << std::endl;
		}
		else {
			for (auto line : code)
				line.printLine();

			parser.parse(code);
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}