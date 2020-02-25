#ifndef OPERAND_HPP
# define OPERAND_HPP

#include "Factory.hpp"

template<typename T>
class Operand : public IOperand {
    public:

        explicit Operand<T>()

    private:
        eOperandType type;
};

#endif