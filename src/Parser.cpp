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

bool Parser::isEmptyStack() {
    return this->operands.empty();
}

bool Parser::isTwoValuesExistInStack() {
    return this->operands.size() < 2;
}

void Parser::parse(code_t &code) {
    std::cout << "\n\n\t\t \e[35m[ Pareser ]\e[0m : parse code phase" << std::endl;

    for (auto line : code) {
        (this->*(this->instructions[line.instruction]))(line);
    };
};

void Parser::push(CodeLine &line) {
    std::cout << "\n\e[35m" << line.instruction << "\e[0m" << std::endl;

    value_t instructionValue = splitInstructionValue(line.value);

    std::cout << INS_VALUE_TYPE << std::endl;
    std::cout << INS_VALUE << std::endl;

    auto operand = Factory::createNewOperand(this->types[INS_VALUE_TYPE], INS_VALUE);

    std::cout << "Operand type: " << operand->getType() << std::endl;
    std::cout << "Operand value: " << operand->toString() << std::endl;

    // put Operand object in the end of the vector with out copying :
    this->operands.emplace_back(operand);
};

void Parser::pop(CodeLine &line) {
    std::cout << "\n\e[35m" << line.instruction << "\e[0m" << std::endl;
};

void Parser::dump(CodeLine &line) {
    std::cout << "\n\e[35m" << line.instruction << "\e[0m" << std::endl;
};

void Parser::assert(CodeLine &line) {
    std::cout << "\n\e[35m" << line.instruction << "\e[0m" << std::endl;
};

void Parser::print(CodeLine &line) {
    std::cout << "\n\e[35m" << line.instruction << "\e[0m" << std::endl;
};

void Parser::exit(CodeLine &line) {
    std::cout << "\n\e[35m" << line.instruction << "\e[0m" << std::endl;
};

// arifmetic operations
void Parser::add(CodeLine &line) {
    std::cout << "\n\e[35m" << line.instruction << "\e[0m" << std::endl;

    if (this->isEmptyStack()) {
		throw Exeptions::EmptyStackOnOpeartionAdd();
    }
	if (this->isTwoValuesExistInStack()) {
		throw Exeptions::NotEnoughOperandsOnOpeartionAdd();
    }

	IOperand const *b = this->operands.back();
    std::cout << "Operand type: " << b->getType() << std::endl;
    std::cout << "Operand value: " << b->toString() << std::endl;
	this->operands.pop_back();
	IOperand const *a = this->operands.back();
    std::cout << "Operand type: " << a->getType() << std::endl;
    std::cout << "Operand value: " << a->toString() << std::endl;
	this->operands.pop_back();

    auto opres = *a + *b;

    std::cout << "Operand type: " << opres->getType() << std::endl;
    std::cout << "Operand value: " << opres->toString() << std::endl;

	this->operands.emplace_back(opres);

	delete (b);
	delete (a);
};

void Parser::sub(CodeLine &line) {
    std::cout << "\n\e[35m" << line.instruction << "\e[0m" << std::endl;

    if (this->isEmptyStack()) {
		throw Exeptions::EmptyStackOnOpeartionSub();
    }
	if (this->isTwoValuesExistInStack()) {
		throw Exeptions::NotEnoughOperandsOnOpeartionSub();
    }

	IOperand const *b = this->operands.back();
    std::cout << "Operand type: " << b->getType() << std::endl;
    std::cout << "Operand value: " << b->toString() << std::endl;
	this->operands.pop_back();
	IOperand const *a = this->operands.back();
    std::cout << "Operand type: " << a->getType() << std::endl;
    std::cout << "Operand value: " << a->toString() << std::endl;
	this->operands.pop_back();

    auto opres = *a - *b;

    std::cout << "Operand type: " << opres->getType() << std::endl;
    std::cout << "Operand value: " << opres->toString() << std::endl;

	this->operands.emplace_back(opres);

	delete (b);
	delete (a);
};

void Parser::mul(CodeLine &line) {
    std::cout << "\n\e[35m" << line.instruction << "\e[0m" << std::endl;

    if (this->isEmptyStack()) {
		throw Exeptions::EmptyStackOnOpeartionMul();
    }
	if (this->isTwoValuesExistInStack()) {
		throw Exeptions::NotEnoughOperandsOnOpeartionMul();
    }

	IOperand const *b = this->operands.back();
    std::cout << "Operand type: " << b->getType() << std::endl;
    std::cout << "Operand value: " << b->toString() << std::endl;
	this->operands.pop_back();
	IOperand const *a = this->operands.back();
    std::cout << "Operand type: " << a->getType() << std::endl;
    std::cout << "Operand value: " << a->toString() << std::endl;
	this->operands.pop_back();

    auto opres = *a * *b;

    std::cout << "Operand type: " << opres->getType() << std::endl;
    std::cout << "Operand value: " << opres->toString() << std::endl;

	this->operands.emplace_back(opres);

	delete (b);
	delete (a);
};

void Parser::div(CodeLine &line) {
    std::cout << "\n\e[35m" << line.instruction << "\e[0m" << std::endl;

    if (this->isEmptyStack()) {
		throw Exeptions::EmptyStackOnOpeartionDiv();
    }
	if (this->isTwoValuesExistInStack()) {
		throw Exeptions::NotEnoughOperandsOnOpeartionDiv();
    }

	IOperand const *b = this->operands.back();
    std::cout << "Operand type: " << b->getType() << std::endl;
    std::cout << "Operand value: " << b->toString() << std::endl;
	this->operands.pop_back();
	IOperand const *a = this->operands.back();
    std::cout << "Operand type: " << a->getType() << std::endl;
    std::cout << "Operand value: " << a->toString() << std::endl;
	this->operands.pop_back();

    auto opres = *a / *b;

    std::cout << "Operand type: " << opres->getType() << std::endl;
    std::cout << "Operand value: " << opres->toString() << std::endl;

	this->operands.emplace_back(opres);

	delete (b);
	delete (a);
};

void Parser::mod(CodeLine &line) {
    std::cout << "\n\e[35m" << line.instruction << "\e[0m" << std::endl;

    if (this->isEmptyStack()) {
		throw Exeptions::EmptyStackOnOpeartionMod();
    }
	if (this->isTwoValuesExistInStack()) {
		throw Exeptions::NotEnoughOperandsOnOpeartionMod();
    }

	IOperand const *b = this->operands.back();
    std::cout << "Operand type: " << b->getType() << std::endl;
    std::cout << "Operand value: " << b->toString() << std::endl;
	this->operands.pop_back();
	IOperand const *a = this->operands.back();
    std::cout << "Operand type: " << a->getType() << std::endl;
    std::cout << "Operand value: " << a->toString() << std::endl;
	this->operands.pop_back();

    auto opres = *a % *b;

    std::cout << "Operand type: " << opres->getType() << std::endl;
    std::cout << "Operand value: " << opres->toString() << std::endl;

	this->operands.emplace_back(opres);

	delete (b);
	delete (a);
};