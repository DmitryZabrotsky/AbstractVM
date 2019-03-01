//
// Created by Dmitry ZABROTSKY on 2019-03-01.
//

#include "Exeptions.hpp"

const char *Exeptions::WrongArgumentsNumber::what() const throw(){
	return "A lot of arguments passed!";
}

const char *Exeptions::WrongFilePath::what() const throw(){
	return "Can't find this file for execute";
}

const char *Exeptions::EmptyFile::what() const throw(){
	return "File is empty";
}



