#include "../incl/Parser.hpp"

Parser::Parser() {
    this->errors = 0;
}

Parser::~Parser() {}

Parser::Parser(Parser const &obj) {
    *this = obj;
}

Parser &Parser::operator=(Parser const &obj) {
    this->errors = obj.errors;
    return (*this);
}

void Parser::splitValue(std::string val) {
    std::replace(val.begin(), val.end(), '(', ' ');

    std::vector<int> array;
    std::stringstream ss(val);
    int temp;
    while (ss >> temp)
        array.push_back(temp);
    }

void Parser::parse(code_t &code) {
    for (auto line : code)
	    std::cout << line.value << std::endl;
}