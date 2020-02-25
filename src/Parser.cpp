#include "Parser.hpp"

Parser::Parser() {}

Parser::~Parser() {}

Parser::Parser(Parser const &obj) {
    *this = obj;
}

Parser &Parser::operator=(Parser const &obj) {
    return (*this);
}