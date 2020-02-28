#ifndef PARSER_HPP
#define PARSER_HPP

#include "Operand.hpp"

typedef std::pair<std::string, std::string> value_t;

#define INS_VALUE_TYPE instructionValue.first
#define INS_VALUE instructionValue.second

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
    value_t splitInstructionValue(std::string typevalue);
};

#endif