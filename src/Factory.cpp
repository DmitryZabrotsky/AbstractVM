#include "../incl/Factory.hpp"

IOperand const * Factory::createOperand(eOperandType type, std::string const & value) const {

    using factoryPtr = IOperand const *(Factory::*)(std::string const &) const;

    constexpr static factoryPtr methods[] = {
		&Factory::createInt8,
		&Factory::createInt16,
		&Factory::createInt32,
		&Factory::createFloat,
		&Factory::createDouble
	};

	return (this->*(methods[type]))(value); // eOperandType type implicitly converts into int
};

IOperand const * Factory::createInt8(std::string const & value) const {
    // return new Operand();
};
IOperand const * Factory::createInt16(std::string const & value) const {
    // return new Operand();
};
IOperand const * Factory::createInt32(std::string const & value) const {
    // return new Operand();
};
IOperand const * Factory::createFloat(std::string const & value) const {
    // return new Operand();
};
IOperand const * Factory::createDouble(std::string const & value) const {
    // return new Operand();
};