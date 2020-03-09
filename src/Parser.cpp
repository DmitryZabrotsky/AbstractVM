#include "../incl/Parser.hpp"

Parser::Parser() {
    this->errors = 0;
    this->types = { {"int8",   Int8}, {"int16",  Int16}, {"int32",  Int32}, {"float",  Float}, {"double", Double} };
    this->instructions = {{"push",   &Parser::push}, {"pop",    &Parser::pop}, {"dump",   &Parser::dump}, {"assert", &Parser::assert},
	{"add",    &Parser::add}, {"sub",    &Parser::sub},	{"mul",    &Parser::mul}, {"div",    &Parser::div}, {"mod",    &Parser::mod},
	{"print",  &Parser::print},	{"exit",   &Parser::exit}};
};

Parser::~Parser() {
    for (auto operand : this->operands)
		delete operand;
	this->operands.clear();
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

void Parser::parse(code_t &code, bool debug) {
    this->debug = debug;

    if (this->debug)
        std::cout << "\e[36;1m[ parser ]\e[0m : parse code phase" << std::endl;

    for (auto line : code) {
        if (!exitins)
            (this->*(this->instructions[line.instruction]))(line);
    };
    if (!exitins)
        throw Exeptions::MissingExitInstruction();
};

void Parser::push(CodeLine &line) {
    if (this->debug)
        std::cout << "\n[ parser ] \e[33;1m" << line.instruction << "\e[0m" << std::endl;

    value_t instructionValue = splitInstructionValue(line.value);

    if (this->debug)
        std::cout << "[ parser ] after split ins val: "  << INS_VALUE_TYPE << " " << INS_VALUE << std::endl;

    auto operand = Factory::createNewOperand(this->types[INS_VALUE_TYPE], INS_VALUE);

    if (this->debug) {
        std::cout << "[ parser ] result operand : type \e[38;5;117;1m" << operand->getType();
        std::cout << "\e[0m value \e[38;5;28;1m" << operand->toString() << "\e[0m" << std::endl;
    }

    // put Operand object in the end of the vector with out copying :
    this->operands.emplace_back(operand);
};

void Parser::pop(CodeLine &line) {
    if (this->debug)
        std::cout << "\n[ parser ] \e[33;1m" << line.instruction << "\e[0m" << std::endl;

    if (this->isEmptyStack()) {
		throw Exeptions::EmptyStackOnOpeartionPop();
    } else {
	    this->operands.pop_back();
    }
};

void Parser::dump(CodeLine &line) {
    if (this->debug)
        std::cout << "\n[ parser ] \e[33;1m" << line.instruction << "\e[0m" << std::endl;

    if (this->isEmptyStack()) {
		throw Exeptions::EmptyStackOnOpeartionPop();
    } else {
        std::for_each(this->operands.rbegin(), this->operands.rend(), [](const auto & operand) {
            std::cout << operand->toString() << std::endl;
        });
    }
};

void Parser::assert(CodeLine &line) {
    if (this->debug)
        std::cout << "\n[ parser ] \e[33;1m" << line.instruction << "\e[0m" << std::endl;

    value_t instructionValue = splitInstructionValue(line.value);

    if (this->debug)
        std::cout << "[ parser ] after split ins val: "  << INS_VALUE_TYPE << " " << INS_VALUE << std::endl;

    auto operand = Factory::createNewOperand(this->types[INS_VALUE_TYPE], INS_VALUE);

    if (this->debug) {
        std::cout << "[ parser ] assert operand : type \e[38;5;117;1m" << operand->getType();
        std::cout << "\e[0m value \e[38;5;28;1m" << operand->toString() << "\e[0m" << std::endl;
    }

    if (this->isEmptyStack()) {
		throw Exeptions::EmptyStackOnOpeartionAssert();
    }
    auto topoperand = this->operands.back();

    if (this->debug) {
        std::cout << "[ parser ] stack operand : type \e[38;5;117;1m" << topoperand->getType();
        std::cout << "\e[0m value \e[38;5;28;1m" << topoperand->toString() << "\e[0m" << std::endl;
    }

    bool res = (topoperand->getType() == operand->getType()) && (topoperand->toString() == operand->toString());

    delete (operand);

    if (!res) {
        throw Exeptions::AssertionFailed();
    }

};

void Parser::print(CodeLine &line) {
    if (this->debug)
        std::cout << "\n[ parser ] \e[33;1m" << line.instruction << "\e[0m" << std::endl;

    if (this->isEmptyStack()) {
		throw Exeptions::EmptyStackOnOpeartionAssert();
    }

    auto topoperand = this->operands.back();

    if (this->debug) {
        std::cout << "[ parser ] stack operand : type \e[38;5;117;1m" << topoperand->getType();
        std::cout << "\e[0m value \e[38;5;28;1m" << topoperand->toString() << "\e[0m" << std::endl;
    }

    bool res = (topoperand->getType() == Int8);
    if (!res) {
        throw Exeptions::AssertionFailed();
    }
    std::cout << static_cast<char>(std::stoll(topoperand->toString())) << std::endl;

};

void Parser::exit(CodeLine &line) {
    if (this->debug)
        std::cout << "\n[ parser ] \e[33;1m" << line.instruction << "\e[0m" << std::endl;

    if (this->exitins) {
        throw Exeptions::MoreThenOneExitOpeartion();
    } else  {
        this->exitins = true;
    }
};

// arifmetic operations
void Parser::add(CodeLine &line) {
    if (this->debug)
        std::cout << "\n[ parser ] \e[33;1m" << line.instruction << "\e[0m" << std::endl;

    if (this->isEmptyStack()) {
		throw Exeptions::EmptyStackOnOpeartionAdd();
    }
	if (this->isTwoValuesExistInStack()) {
		throw Exeptions::NotEnoughOperandsOnOpeartionAdd();
    }

	IOperand const *b = this->operands.back();
    if (this->debug) {
        std::cout << "[ parser ] b : type \e[38;5;117;1m" << b->getType();
        std::cout << "\e[0m value \e[38;5;28;1m" << b->toString() << "\e[0m" << std::endl;
    }
    this->operands.pop_back();

	IOperand const *a = this->operands.back();
    if (this->debug) {
        std::cout << "[ parser ] a : type \e[38;5;117;1m" << a->getType();
        std::cout << "\e[0m value \e[38;5;28;1m" << a->toString() << "\e[0m" << std::endl;
    }
	this->operands.pop_back();

    auto opres = *a + *b;

    if (this->debug) {
        std::cout << "[ parser ] opres : type \e[38;5;117;1m" << opres->getType();
        std::cout << "\e[0m value \e[38;5;28;1m" << opres->toString() << "\e[0m" << std::endl;
    }

    this->operands.emplace_back(opres);

	delete (b);
	delete (a);
};

void Parser::sub(CodeLine &line) {
    if (this->debug)
        std::cout << "\n[ parser ] \e[33;1m" << line.instruction << "\e[0m" << std::endl;

    if (this->isEmptyStack()) {
		throw Exeptions::EmptyStackOnOpeartionSub();
    }
	if (this->isTwoValuesExistInStack()) {
		throw Exeptions::NotEnoughOperandsOnOpeartionSub();
    }

	IOperand const *b = this->operands.back();
    if (this->debug) {
        std::cout << "[ parser ] b : type \e[38;5;117;1m" << b->getType();
        std::cout << "\e[0m value \e[38;5;28;1m" << b->toString() << "\e[0m" << std::endl;
    }
    this->operands.pop_back();

	IOperand const *a = this->operands.back();
    if (this->debug) {
        std::cout << "[ parser ] a : type \e[38;5;117;1m" << a->getType();
        std::cout << "\e[0m value \e[38;5;28;1m" << a->toString() << "\e[0m" << std::endl;
    }
	this->operands.pop_back();

    auto opres = *a - *b;

    if (this->debug) {
        std::cout << "[ parser ] opres : type \e[38;5;117;1m" << opres->getType();
        std::cout << "\e[0m value \e[38;5;28;1m" << opres->toString() << "\e[0m" << std::endl;
    }

	this->operands.emplace_back(opres);

	delete (b);
	delete (a);
};

void Parser::mul(CodeLine &line) {
    if (this->debug)
        std::cout << "\n[ parser ] \e[33;1m" << line.instruction << "\e[0m" << std::endl;

    if (this->isEmptyStack()) {
		throw Exeptions::EmptyStackOnOpeartionMul();
    }
	if (this->isTwoValuesExistInStack()) {
		throw Exeptions::NotEnoughOperandsOnOpeartionMul();
    }

	IOperand const *b = this->operands.back();
    if (this->debug) {
        std::cout << "[ parser ] b : type \e[38;5;117;1m" << b->getType();
        std::cout << "\e[0m value \e[38;5;28;1m" << b->toString() << "\e[0m" << std::endl;
    }
    this->operands.pop_back();

	IOperand const *a = this->operands.back();
    if (this->debug) {
        std::cout << "[ parser ] a : type \e[38;5;117;1m" << a->getType();
        std::cout << "\e[0m value \e[38;5;28;1m" << a->toString() << "\e[0m" << std::endl;
    }
	this->operands.pop_back();

    auto opres = *a * *b;

    if (this->debug) {
        std::cout << "[ parser ] opres : type \e[38;5;117;1m" << opres->getType();
        std::cout << "\e[0m value \e[38;5;28;1m" << opres->toString() << "\e[0m" << std::endl;
    }

	this->operands.emplace_back(opres);

	delete (b);
	delete (a);
};

void Parser::div(CodeLine &line) {
    if (this->debug)
        std::cout << "\n[ parser ] \e[33;1m" << line.instruction << "\e[0m" << std::endl;

    if (this->isEmptyStack()) {
		throw Exeptions::EmptyStackOnOpeartionDiv();
    }
	if (this->isTwoValuesExistInStack()) {
		throw Exeptions::NotEnoughOperandsOnOpeartionDiv();
    }

	IOperand const *b = this->operands.back();
    if (this->debug) {
        std::cout << "[ parser ] b : type \e[38;5;117;1m" << b->getType();
        std::cout << "\e[0m value \e[38;5;28;1m" << b->toString() << "\e[0m" << std::endl;
    }
	this->operands.pop_back();

	IOperand const *a = this->operands.back();
    if (this->debug) {
        std::cout << "[ parser ] a : type \e[38;5;117;1m" << a->getType();
        std::cout << "\e[0m value \e[38;5;28;1m" << a->toString() << "\e[0m" << std::endl;
    }
	this->operands.pop_back();

    auto opres = *a / *b;

    if (this->debug) {
        std::cout << "[ parser ] opres : type \e[38;5;117;1m" << opres->getType();
        std::cout << "\e[0m value \e[38;5;28;1m" << opres->toString() << "\e[0m" << std::endl;
    }

	this->operands.emplace_back(opres);

	delete (b);
	delete (a);
};

void Parser::mod(CodeLine &line) {
    if (this->debug)
        std::cout << "\n[ parser ] \e[33;1m" << line.instruction << "\e[0m" << std::endl;

    if (this->isEmptyStack()) {
		throw Exeptions::EmptyStackOnOpeartionMod();
    }
	if (this->isTwoValuesExistInStack()) {
		throw Exeptions::NotEnoughOperandsOnOpeartionMod();
    }

	IOperand const *b = this->operands.back();
    if (this->debug) {
        std::cout << "[ parser ] b : type \e[38;5;117;1m" << b->getType();
        std::cout << "\e[0m value \e[38;5;28;1m" << b->toString() << "\e[0m" << std::endl;
    }
	this->operands.pop_back();

	IOperand const *a = this->operands.back();
    if (this->debug) {
        std::cout << "[ parser ] a : type \e[38;5;117;1m" << a->getType();
        std::cout << "\e[0m value \e[38;5;28;1m" << a->toString() << "\e[0m" << std::endl;
    }
	this->operands.pop_back();

    auto opres = *a % *b;

    if (this->debug) {
        std::cout << "[ parser ] opres : type \e[38;5;117;1m" << opres->getType();
        std::cout << "\e[0m value \e[38;5;28;1m" << opres->toString() << "\e[0m" << std::endl;
    }

    this->operands.emplace_back(opres);

	delete (b);
	delete (a);
};