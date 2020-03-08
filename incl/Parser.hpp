#ifndef PARSER_HPP
#define PARSER_HPP

#include "Operand.hpp"

typedef std::pair<std::string, std::string> value_t;
typedef std::vector<IOperand const *> operands_t;
typedef std::map<std::string, eOperandType> types_t;

#define INS_VALUE_TYPE instructionValue.first
#define INS_VALUE instructionValue.second

class Parser {
public:

    int errors;
    bool exitins;

    Parser();
    ~Parser();

    Parser(Parser const &obj) = delete;
    Parser &operator=(Parser const &obj) = delete;

    void parse(code_t &code);

private:

    operands_t operands;
    types_t types;
    std::map<std::string, void (Parser::*)(CodeLine &)> instructions;

    void splitValue(std::string val);
    value_t splitInstructionValue(std::string typevalue);
    bool isEmptyStack();
    bool isTwoValuesExistInStack();

	void push(CodeLine &line);
	void pop(CodeLine &line);
	void dump(CodeLine &line);
	void assert(CodeLine &line);
	void print(CodeLine &line);
	void exit(CodeLine &line);
	void add(CodeLine &line);
	void sub(CodeLine &line);
	void mul(CodeLine &line);
	void div(CodeLine &line);
	void mod(CodeLine &line);

    void printInfoAboutOperand(IOperand const * opearnd);
};

#endif