//
// Created by Dmitry ZABROTSKY on 2019-03-01.
//

#ifndef EXEPTIONS_HPP
#define EXEPTIONS_HPP

#include <exception>

class Exeptions {

public:
	class WrongArgumentsNumber : public std::exception {
	public:
		const char *what() const noexcept override;
	};
	class WrongFilePath : public std::exception {
	public:
		const char *what() const noexcept override;
	};
	class EmptyFile : public std::exception {
	public:
		const char *what() const noexcept override;
	};
	class CodeError : public std::exception {
	public:
		const char *what() const noexcept override;
	};
	class InvalidExpression : public std::exception {
	public:
		const char *what() const noexcept override;
	};
	class InvalidInstraction : public std::exception {
	public:
		const char *what() const noexcept override;
	};
	class InvalidValue : public std::exception {
	public:
		const char *what() const noexcept override;
	};
	class MissingInstructionValue : public std::exception {
	public:
		const char *what() const noexcept override;
	};
};

#endif
