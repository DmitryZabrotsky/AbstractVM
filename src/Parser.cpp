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

value_t Parser::splitInstructionValue(std::string typevalue) {
    value_t res;

    std::size_t start = typevalue.find('(');
	std::size_t end = typevalue.find(')') - start;
	std::string type = typevalue.substr(0, start);
	std::string value = typevalue.substr(start + 1, end - 1);
    res = std::make_pair(type, value);
    return res;
}

void Parser::parse(code_t &code) {
    std::cout << "\n\nDEBUG\t[ Pareser ] : parse code phase" << std::endl;
    for (auto line : code)
        if (!line.value.empty()) {
	        std::cout << line.value << std::endl;
            value_t instructionValue = splitInstructionValue(line.value);
	        std::cout << INS_VALUE_TYPE << std::endl;
	        std::cout << INS_VALUE << std::endl;
        }
}