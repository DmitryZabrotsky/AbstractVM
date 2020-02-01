#ifndef LEXER_HPP
#define LEXER_HPP

#include "CodeLine.hpp"

class Lexer {
public:
    int errors;

    Lexer();
    ~Lexer();
    Lexer(Lexer const &obj);

    Lexer &operator=(Lexer const &obj);

    void handle(int ac, char const **av);

private:
    void handleFile(std::string path);
	void handleConsole();
	bool verifyString(std::string str, size_t i);
    void eraseComment(std::string &str);
};

#endif