//
// Created by Dmitry ZABROTSKY on 2019-03-01.
//

#include "Exeptions.hpp"

const char *Exeptions::WrongArgumentsNumber::what() const noexcept {
	return "A lot of arguments passed!";
}

const char *Exeptions::WrongFilePath::what() const noexcept {
	return "Wrong file path";
}

const char *Exeptions::EmptyFile::what() const noexcept {
	return "File is empty";
}

const char *Exeptions::CodeError::what() const noexcept {
	return "Code error!";
}

const char *Exeptions::InvalidExpression::what() const noexcept {
	return "Invalid expression";
}

const char *Exeptions::InvalidInstraction::what() const noexcept {
	return "Invalid instraction";
}

const char *Exeptions::InvalidValue::what() const noexcept {
	return "Invalid value";
}

const char *Exeptions::MissingInstructionValue::what() const noexcept {
	return "Missing instruction value";
}
