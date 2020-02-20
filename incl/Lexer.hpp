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

    void handle(int ac, char const **av, std::vector<CodeLine> &code);

private:
    void handleFile(std::string path, std::vector<CodeLine> &code);
	void handleConsole(std::vector<CodeLine> &code);

    // bool verifyString(std::string str, size_t i);

    std::pair<bool, size_t> checkGrammar(std::vector<std::string> &tokens);
    bool checkInstruction(std::vector<std::string> &tokens);
    bool checkInstructionWithValue(std::vector<std::string> &tokens);

    void eraseComment(std::string &str);
    std::vector<std::string> splitLine(std::string &line);
};

#endif