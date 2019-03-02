#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <list>
#include <exception>
#include <fstream>
#include "Exeptions.hpp"

#include <iostream>

class Parser {
public:
    std::list<std::string> program;

    Parser();
    ~Parser();
    Parser(Parser const &obj);

    Parser &operator=(Parser const &obj);

    void parse(int ac, char const **av);

private:
    void parseFile(std::string path);
	void parseConsole();

};

#endif