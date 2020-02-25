#ifndef CODELINE_HPP
# define CODELINE_HPP

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

    void writeError(std::string);

    CodeLine &operator=(CodeLine const &obj);

    void printError();
    void printLine();
};

#endif