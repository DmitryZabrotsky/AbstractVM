#include "../incl/Parser.hpp"

bool ifDebug(int ac, char const **av) {
	for (int i = 1; i < ac; i++) {
		std::string arg = av[i];
		if (arg == "-d")
			return true;
	}
	return false;
}

int main(int ac, char const **av)
{
	bool debug = ifDebug(ac, av);

	if (debug)
		std::cout << "\e[32;1mDEBUG ON\e[0m\n" << std::endl;

    code_t code;
	Lexer lexer;
	Parser parser;
	try {
		lexer.handle(ac, av, code, debug);
		if (lexer.errors > 0) {
			std::string msg = "Total \e[31;1merrors\e[0m after lexer phase : " + std::to_string(lexer.errors) + "\n";
			std::cout << msg << std::endl;
			for (auto line : code)
				line.printError();
			std::cout << std::endl;
		}
		else {
			if (debug) {
				for (auto line : code)
					line.printLine();
			}

			parser.parse(code, debug);
		}
	}
	catch (std::exception& e) {
		std::cout << "\e[31;1m" << e.what() << "\e[0m" << std::endl;
	}
	return 0;
}