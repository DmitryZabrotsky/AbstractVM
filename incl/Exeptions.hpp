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

	class ValueOverflowExeption : public std::exception {
	public:
		const char *what() const noexcept override;
	};

	class ValueUnderflowExeption : public std::exception {
	public:
		const char *what() const noexcept override;
	};

	class DivisionByZero : public std::exception {
	public:
		const char *what() const noexcept override;
	};

	class ModuloByZero : public std::exception {
	public:
		const char *what() const noexcept override;
	};

	class EmptyStackOnOpeartionAdd : public std::exception {
	public:
		const char *what() const noexcept override;
	};

	class NotEnoughOperandsOnOpeartionAdd : public std::exception {
	public:
		const char *what() const noexcept override;
	};

	class EmptyStackOnOpeartionSub : public std::exception {
		public:
		const char *what() const noexcept override;
	};

	class NotEnoughOperandsOnOpeartionSub : public std::exception {
	public:
		const char *what() const noexcept override;
	};

	class EmptyStackOnOpeartionMul : public std::exception {
		public:
		const char *what() const noexcept override;
	};

	class NotEnoughOperandsOnOpeartionMul : public std::exception {
	public:
		const char *what() const noexcept override;
	};

	class EmptyStackOnOpeartionDiv : public std::exception {
		public:
		const char *what() const noexcept override;
	};

	class NotEnoughOperandsOnOpeartionDiv : public std::exception {
	public:
		const char *what() const noexcept override;
	};

	class EmptyStackOnOpeartionMod : public std::exception {
		public:
		const char *what() const noexcept override;
	};
	class NotEnoughOperandsOnOpeartionMod : public std::exception {
		public:
		const char *what() const noexcept override;
	};

	class EmptyStackOnOpeartionPop : public std::exception {
		public:
		const char *what() const noexcept override;
	};

	class EmptyStackOnOpeartionAssert : public std::exception {
		public:
		const char *what() const noexcept override;
	};

	class AssertionFailed : public std::exception {
		public:
		const char *what() const noexcept override;
	};

	class MoreThenOneExitOpeartion : public std::exception {
		public:
		const char *what() const noexcept override;
	};
};

#endif
