#ifndef CODELINE_HPP
#define CODELINE_HPP

#include "header.h"

class CodeLine {
public:
    int number;
    std::string operation;
    std::string value;
    std::pair<bool, std::string> error;

    CodeLine();
    ~CodeLine();
    CodeLine(CodeLine const &obj);

    CodeLine(int num, std::string op, std::string val, std::string err);

    CodeLine &operator=(CodeLine const &obj);
};

#endif