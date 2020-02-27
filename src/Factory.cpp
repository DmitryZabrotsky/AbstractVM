#include "../incl/Operand.hpp"

IOperand const * Factory::createNewOperand(eOperandType type, std::string const &value) {
	static Factory factory;
	return factory.createOperand(type, value);
}

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
    return new Operand<int8_t>(Int8, value);
};
IOperand const * Factory::createInt16(std::string const & value) const {
    return new Operand<int16_t>(Int16, value);
};
IOperand const * Factory::createInt32(std::string const & value) const {
    return new Operand<int32_t>(Int32, value);
};
IOperand const * Factory::createFloat(std::string const & value) const {
    return new Operand<float>(Float, value);
};
IOperand const * Factory::createDouble(std::string const & value) const {
    return new Operand<double>(Double, value);
};