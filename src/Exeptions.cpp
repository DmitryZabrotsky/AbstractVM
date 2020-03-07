//
// Created by Dmitry ZABROTSKY on 2019-03-01.
//

#include "Exeptions.hpp"

const char *Exeptions::WrongArgumentsNumber::what() const noexcept {
	return "A lot of arguments passed!";
};

const char *Exeptions::WrongFilePath::what() const noexcept {
	return "Wrong file path";
};

const char *Exeptions::EmptyFile::what() const noexcept {
	return "File is empty";
};

const char *Exeptions::CodeError::what() const noexcept {
	return "Code error!";
};

const char *Exeptions::InvalidExpression::what() const noexcept {
	return "Invalid expression";
};

const char *Exeptions::InvalidInstraction::what() const noexcept {
	return "Invalid instraction";
};

const char *Exeptions::InvalidValue::what() const noexcept {
	return "Invalid value";
};

const char *Exeptions::MissingInstructionValue::what() const noexcept {
	return "Missing instruction value";
};

const char *Exeptions::ValueOverflowExeption::what() const noexcept {
	return "Overflow value";
};

const char *Exeptions::ValueUnderflowExeption::what() const noexcept {
	return "Underflow value";
};

const char *Exeptions::DivisionByZero::what() const noexcept {
	return "Division by zero";
};

const char *Exeptions::ModuloByZero::what() const noexcept {
	return "Modulo by zero";
};

const char *Exeptions::EmptyStackOnOpeartionAdd::what() const noexcept {
	return "Empty stack on opearation add";
};

const char *Exeptions::NotEnoughOperandsOnOpeartionAdd::what() const noexcept {
	return "Not enough operands on opeartion add";
};

const char *Exeptions::EmptyStackOnOpeartionSub::what() const noexcept {
	return "Empty stack on opearation sub";
};

const char *Exeptions::NotEnoughOperandsOnOpeartionSub::what() const noexcept {
	return "Not enough operands on opeartion sub";
};

const char *Exeptions::EmptyStackOnOpeartionMul::what() const noexcept {
	return "Empty stack on opearation mul";
};

const char *Exeptions::NotEnoughOperandsOnOpeartionMul::what() const noexcept {
	return "Not enough operands on opeartion mul";
};

const char *Exeptions::EmptyStackOnOpeartionDiv::what() const noexcept {
	return "Empty stack on opearation div";
};

const char *Exeptions::NotEnoughOperandsOnOpeartionDiv::what() const noexcept {
	return "Not enough operands on opeartion div";
};

const char *Exeptions::EmptyStackOnOpeartionMod::what() const noexcept {
	return "Empty stack on opearation mod";
};

const char *Exeptions::NotEnoughOperandsOnOpeartionMod::what() const noexcept {
	return "Not enough operands on opeartion mod";
};
