#include "CodeLine.hpp"

CodeLine::CodeLine() {}

// CodeLine::CodeLine(int num, std::string op, std::string val, std::string err) :
// number(num), instruction(op), value(val)
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
    this->instruction = obj.instruction;
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

void CodeLine::printError() {
    if (this->error.first)
        std::cout << this->error.second << std::endl;
}

void CodeLine::printLine() {
    std::cout << "\nnum: " << this->number << std::endl;
    std::cout << "opn: " << this->instruction << std::endl;
    std::cout << "val: " << this->value << std::endl;
    std::cout << "err: " << this->error.first << "\tmsg: " << this->error.second << "\n" << std::endl;
}
