#ifndef PARSER_HPP
#define PARSER_HPP

#include "Operand.hpp"

class Parser {
public:

    int errors;

    Parser();
    ~Parser();
    Parser(Parser const &obj);

    Parser &operator=(Parser const &obj);

    void parse(code_t &code);

private:
    void splitValue(std::string val);
};

#endif