#ifndef OPERAND_HPP
# define OPERAND_HPP

#include "Factory.hpp"

template<typename T>
class Operand : public IOperand {
    public:

        explicit Operand<T>(eOperandType type, std::string value) : type(type), value(value) {}

        Operand() = delete;

        Operand(Operand const &obj) = delete;

        ~Operand() override = default;

        Operand &operator=(Operand const &obj) = delete;

        eOperandType getType() const override {
            return this->type;
        }

        std::string const &toString() const override {
            return this->value;
        };

        int getPrecision() const override {
            return this->type;
        };

        IOperand const * operator+( IOperand const & operand ) const override {
            eOperandType resType;
		    std::string resValue;

            if (type > operand.getType()) {
                resType = type;
            } else {
                operand.getType();
            }

            if (resType > Int32) {
    		    resValue = std::to_string(std::stold(toString()) + std::stold(operand.toString()));
            } else {
    		    resValue = std::to_string(std::stoll(toString()) + std::stoll(operand.toString()));
            }

            std::cout << "IOperand operator+ " << std::endl;

            return Factory::createNewOperand(resType, resValue);
        };
		IOperand const * operator-( IOperand const & operand ) const override {
            eOperandType resType;
		    std::string resValue;

            if (type > operand.getType()) {
                resType = type;
            } else {
                operand.getType();
            }

            if (resType > Int32) {
    		    resValue = std::to_string(std::stold(toString()) - std::stold(operand.toString()));
            } else {
    		    resValue = std::to_string(std::stoll(toString()) - std::stoll(operand.toString()));
            }

            std::cout << "IOperand operator- " << std::endl;

            return Factory::createNewOperand(resType, "pisos42");
        };
		IOperand const * operator*( IOperand const & operand ) const override {
            eOperandType resType;
		    std::string resValue;

            if (type > operand.getType()) {
                resType = type;
            } else {
                operand.getType();
            }

            if (resType > Int32) {
    		    resValue = std::to_string(std::stold(toString()) * std::stold(operand.toString()));
            } else {
    		    resValue = std::to_string(std::stoll(toString()) * std::stoll(operand.toString()));
            }

            std::cout << "IOperand operator* " << std::endl;

            return Factory::createNewOperand(resType, "pisos42");
        };
		IOperand const * operator/( IOperand const & operand ) const override {
            eOperandType resType;
		    std::string resValue;

            if (type > operand.getType()) {
                resType = type;
            } else {
                operand.getType();
            }

            if (resType > Int32) {
    		    resValue = std::to_string(std::stold(toString()) / std::stold(operand.toString()));
            } else {
    		    resValue = std::to_string(std::stoll(toString()) / std::stoll(operand.toString()));
            }

            std::cout << "IOperand operator/ " << std::endl;

            return Factory::createNewOperand(resType, "pisos42");
        };
		IOperand const * operator%( IOperand const & operand ) const override {
            eOperandType resType;
		    std::string resValue;

            if (type > operand.getType()) {
                resType = type;
            } else {
                operand.getType();
            }

            if (resType > Int32) {
                resValue = std::to_string(fmod(std::stold(toString()), std::stold(operand.toString())));
            } else {
                resValue = std::to_string(std::stoll(toString()) % std::stoll(operand.toString()));
            }

            std::cout << "IOperand operator% " << std::endl;

            return Factory::createNewOperand(resType, "pisos42");
        };


    private:
        eOperandType type;
        std::string value;
};

#endif