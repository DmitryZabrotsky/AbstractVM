#include "../incl/Parser.hpp"

Parser::Parser() {
    this->errors = 0;
    this->types = { {"int8",   Int8}, {"int16",  Int16}, {"int32",  Int32}, {"float",  Float}, {"double", Double} };
    this->instructions = {{"push",   &Parser::push}, {"pop",    &Parser::pop}, {"dump",   &Parser::dump}, {"assert", &Parser::assert},
	{"add",    &Parser::add}, {"sub",    &Parser::sub},	{"mul",    &Parser::mul}, {"div",    &Parser::div}, {"mod",    &Parser::mod},
	{"print",  &Parser::print},	{"exit",   &Parser::exit}};
};

Parser::~Parser() {};

Parser::Parser(Parser const &obj) {
    *this = obj;
};

Parser &Parser::operator=(Parser const &obj) {
    this->errors = obj.errors;
    return (*this);
};

value_t Parser::splitInstructionValue(std::string typevalue) {
    value_t res;

    std::size_t start = typevalue.find('(');
	std::size_t end = typevalue.find(')') - start;
	std::string type = typevalue.substr(0, start);
	std::string value = typevalue.substr(start + 1, end - 1);
    res = std::make_pair(type, value);
    return res;
};

void Parser::parse(code_t &code) {
    std::cout << "\n\n\t\t \e[35m[ Pareser ]\e[0m : parse code phase" << std::endl;

    for (auto line : code) {
        (this->*(this->instructions[line.instruction]))(line);
    };
};

void Parser::push(CodeLine &line) {
    std::cout << "\e[35m" << line.instruction << "\e[0m" << std::endl;

    value_t instructionValue = splitInstructionValue(line.value);

    std::cout << INS_VALUE_TYPE << std::endl;
    std::cout << INS_VALUE << std::endl;

    auto operand = Factory::createNewOperand(this->types[INS_VALUE_TYPE], INS_VALUE);
    std::cout << "Operand type: " << operand->getType() << std::endl;;
    std::cout << "Operand value: " << operand->toString() << std::endl;;

    // direct creating Operand object in the end of the vector with out copying :
    this->operands.emplace_back(Factory::createNewOperand(this->types[INS_VALUE_TYPE], INS_VALUE));
};

void Parser::pop(CodeLine &line) {
    std::cout << "\e[35m" << line.instruction << "\e[0m" << std::endl;
};

void Parser::dump(CodeLine &line) {
    std::cout << "\e[35m" << line.instruction << "\e[0m" << std::endl;
};

void Parser::assert(CodeLine &line) {
    std::cout << "\e[35m" << line.instruction << "\e[0m" << std::endl;
};

void Parser::add(CodeLine &line) {
    std::cout << "\e[35m" << line.instruction << "\e[0m" << std::endl;
};

void Parser::sub(CodeLine &line) {
    std::cout << "\e[35m" << line.instruction << "\e[0m" << std::endl;
};

void Parser::mul(CodeLine &line) {
    std::cout << "\e[35m" << line.instruction << "\e[0m" << std::endl;
};

void Parser::div(CodeLine &line) {
    std::cout << "\e[35m" << line.instruction << "\e[0m" << std::endl;
};

void Parser::mod(CodeLine &line) {
    std::cout << "\e[35m" << line.instruction << "\e[0m" << std::endl;
};

void Parser::print(CodeLine &line) {
    std::cout << "\e[35m" << line.instruction << "\e[0m" << std::endl;
};

void Parser::exit(CodeLine &line) {
    std::cout << "\e[35m" << line.instruction << "\e[0m" << std::endl;
};