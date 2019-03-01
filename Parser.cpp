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
    std::cout << "file parsing from - " << path << std::endl;
}

void Parser::parseConsole() {
    std::cout << "console parsing" << std::endl;
}
