#include "CodeLine.hpp"

CodeLine::CodeLine() {}

// CodeLine::CodeLine(int num, std::string op, std::string val, std::string err) :
// number(num), operation(op), value(val)
// {
//     if (!err.empty()) {
//         this->error = std::make_pair(true, err);
//     } else {
//         this->error = std::make_pair(false, "");
//     }
// }

CodeLine::~CodeLine() {}

CodeLine::CodeLine(CodeLine const &obj) {
    *this = obj;
}

CodeLine &CodeLine::operator=(CodeLine const &obj) {
    this->number = obj.number;
    this->operation = obj.operation;
    this->value = obj.value;
    this->error = obj.error;
    return (*this);
}

void CodeLine::writeError(std::string err) {
    if (!err.empty()) {
        this->error = std::make_pair(true, err);
    } else {
        this->error = std::make_pair(false, "");
    }
}

void CodeLine::printLine() {
    std::cout << "num: " << this->number << "\n" << std::endl;
    std::cout << "opn: " << this->operation << "\n" << std::endl;
    std::cout << "val: " << this->value << "\n" << std::endl;
    std::cout << "err: " << this->error.first << " " << this->error.second << std::endl;
}
