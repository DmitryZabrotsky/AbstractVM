//
// Created by Dmitry ZABROTSKY on 2019-03-01.
//

#include "Exeptions.hpp"

const char *Exeptions::WrongArgumentsNumber::what() const throw(){
	return "A lot of arguments passed!";
}

const char *Exeptions::WrongFilePath::what() const throw(){
	return "Wrong file path";
}

const char *Exeptions::EmptyFile::what() const throw(){
	return "File is empty";
}

const char *Exeptions::CodeError::what() const throw(){
	return "Code error!";
}

const char *Exeptions::InvalidExpression::what() const throw(){
	return "Invalid expression";
}

const char *Exeptions::InvalidInstraction::what() const throw(){
	return "Invalid instraction";
}

const char *Exeptions::InvalidValue::what() const throw(){
	return "Invalid value";
}



