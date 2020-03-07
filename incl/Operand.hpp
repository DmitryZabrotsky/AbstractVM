#ifndef OPERAND_HPP
# define OPERAND_HPP

#include "Factory.hpp"

template<typename T>
class Operand : public IOperand {
    private:
        eOperandType type;
        std::string value;

    public:
        explicit Operand<T>(eOperandType type, std::string value) : type(type), value(value) {
            switch (type) {
                case Int8: {
                    long long val = std::stoll(value);

                    std::cout << std::to_string(val) << " max: " << SCHAR_MAX << " min: " <<  SCHAR_MIN << std::endl;

                    if (val > SCHAR_MAX) {
                        throw Exeptions::ValueOverflowExeption();
                    } else if (val < SCHAR_MIN) {
                        throw Exeptions::ValueUnderflowExeption();
                    };
                    break;
                }

                case Int16: {
                    long long val = std::stoll(value);

                    std::cout << std::to_string(val) << " max: " << SHRT_MAX << " min: " <<  SHRT_MIN << std::endl;

                    if (val > SHRT_MAX) {
                        throw Exeptions::ValueOverflowExeption();
                    } else if (val < SHRT_MIN) {
                        throw Exeptions::ValueUnderflowExeption();
                    };
                    break;
                }

                case Int32: {
                    long long val = std::stoll(value);

                    std::cout << std::to_string(val) << " max: " << INT_MAX << " min: " <<  INT_MIN << std::endl;

                    if (val > INT_MAX) {
                        throw Exeptions::ValueOverflowExeption();
                    } else if (val < INT_MIN) {
                        throw Exeptions::ValueUnderflowExeption();
                    };
                    break;
                }

                case Float: {
                    long double val = std::stod(value);

                    std::cout << std::to_string(val) << " max: " << FLT_MAX << " min: " <<  -FLT_MAX << std::endl;

                    if (val > FLT_MAX) {
                        throw Exeptions::ValueOverflowExeption();
                    } else if (val < -FLT_MAX) {
                        throw Exeptions::ValueUnderflowExeption();
                    };
                    break;
                }

                case Double: {
                    long double val = std::stod(value);

                    std::cout << std::to_string(val) << " max: " << DBL_MAX << " min: " <<  -DBL_MAX << std::endl;

                    if (val > DBL_MAX) {
                        throw Exeptions::ValueOverflowExeption();
                    } else if (val < -DBL_MAX) {
                        throw Exeptions::ValueUnderflowExeption();
                    };
                    break;
                }
            };
        };

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
                resType = this->type;
            } else {
                resType = operand.getType();
            }

            if (resType > Int32) {
    		    resValue = std::to_string(std::stold(this->toString()) + std::stold(operand.toString()));
            } else {
    		    resValue = std::to_string(std::stoll(this->toString()) + std::stoll(operand.toString()));
            }

            std::cout << "IOperand operator+ " << std::endl;

            return Factory::createNewOperand(resType, resValue);
        };
		IOperand const * operator-( IOperand const & operand ) const override {
            eOperandType resType;
		    std::string resValue;

            if (type > operand.getType()) {
                resType = this->type;
            } else {
                resType = operand.getType();
            }

            if (resType > Int32) {
    		    resValue = std::to_string(std::stold(this->toString()) - std::stold(operand.toString()));
            } else {
    		    resValue = std::to_string(std::stoll(this->toString()) - std::stoll(operand.toString()));
            }

            std::cout << "IOperand operator- " << std::endl;

            return Factory::createNewOperand(resType, resValue);
        };
		IOperand const * operator*( IOperand const & operand ) const override {
            eOperandType resType;
		    std::string resValue;

            if (type > operand.getType()) {
                resType = this->type;
            } else {
                resType = operand.getType();
            }

            if (resType > Int32) {
    		    resValue = std::to_string(std::stold(this->toString()) * std::stold(operand.toString()));
            } else {
    		    resValue = std::to_string(std::stoll(this->toString()) * std::stoll(operand.toString()));
            }

            std::cout << "IOperand operator* " << std::endl;

            return Factory::createNewOperand(resType, resValue);
        };

        bool isZero(eOperandType const type, std::string const &val) const {
            bool res;

            if (type > Int32) {
                res = std::stold(val) == 0.0;
            } else {
                res = std::stoll(val) == 0;
            }
            return res;
        };

		IOperand const * operator/( IOperand const & operand ) const override {
            eOperandType resType;
		    std::string resValue;

            if (type > operand.getType()) {
                resType = this->type;
            } else {
                resType = operand.getType();
            }

            if (isZero(resType, operand.toString())) {
                throw Exeptions::DivisionByZero();
            }

            if (resType > Int32) {
    		    resValue = std::to_string(std::stold(this->toString()) / std::stold(operand.toString()));
            } else {
    		    resValue = std::to_string(std::stoll(this->toString()) / std::stoll(operand.toString()));
            }

            std::cout << "IOperand operator/ " << std::endl;

            return Factory::createNewOperand(resType, resValue);
        };
		IOperand const * operator%( IOperand const & operand ) const override {
            eOperandType resType;
		    std::string resValue;

            if (type > operand.getType()) {
                resType = this->type;
            } else {
                resType = operand.getType();
            }

            if (isZero(resType, operand.toString())) {
                throw Exeptions::ModuloByZero();
            }

            if (resType > Int32) {
                resValue = std::to_string(fmod(std::stold(this->toString()), std::stold(operand.toString())));
            } else {
                resValue = std::to_string(std::stoll(this->toString()) % std::stoll(operand.toString()));
            }

            std::cout << "IOperand operator% " << std::endl;

            return Factory::createNewOperand(resType, resValue);
        };
};

#endif