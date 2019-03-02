#include <regex>
#include "Parser.hpp"

Parser::Parser() {}

Parser::~Parser() {}

Parser::Parser(Parser const &obj) {
    *this = obj;
}

Parser &Parser::operator=(Parser const &obj) {
    this->program = obj.program;
    return (*this);
}

void Parser::parse(int ac, char const **av) {
    switch (ac) {
        case 1:
            parseConsole();
            break;
        case 2:
            parseFile(av[1]);
            break;
        default:
            throw Exeptions::WrongArgumentsNumber();
    }
}

void Parser::parseFile(std::string path) {
    std::ifstream stream(path);

    if (!stream.is_open()) {
        throw Exeptions::WrongFilePath();
    }
    else if (stream.peek() == std::ifstream::traits_type::eof()) {
        throw Exeptions::EmptyFile();
    }
    else {
        std::string buff;

        while (std::getline(stream, buff))
        {
            std::cout << buff;
            if (!stream.eof())
                std::cout << "\n";
        }
        stream.close();
    }
}

void Parser::parseConsole() {
	std::string buff;

	while (true) {
		std::getline(std::cin, buff);
		if (buff == ";;") {
			break;
		}
		std::cout << buff << std::endl;
	}
}

bool verifyString(std::string str) {
	std::regex integers("^(push|assert)[\\s]+(int8|int16|int32)[(][-]?\\d+[)]");
	std::regex floats("^(push|assert)[\\s]+(float|double)[(][-]?\\d+(.[0-9]+)[)]");
	std::regex instructions("");
}
