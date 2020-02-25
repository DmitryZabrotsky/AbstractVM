#ifndef LEXER_HPP
# define LEXER_HPP

#include "CodeLine.hpp"

#define OPERATION tokens[0]
#define VALUE tokens[1]

typedef std::vector<std::string> tokens_t;
typedef std::vector<CodeLine> code_t;

class Lexer {
public:
    int errors;

    Lexer();
    ~Lexer();
    Lexer(Lexer const &obj);

    Lexer &operator=(Lexer const &obj);

    void handle(int ac, char const **av, code_t &code);

private:
    void handleFile(std::string path, code_t &code);
	void handleConsole(code_t &code);

    // bool verifyString(std::string str, size_t i);

    std::pair<bool, size_t> checkGrammar(tokens_t &tokens);
    bool checkInstruction(tokens_t &tokens);
    bool checkInstructionWithValue(tokens_t &tokens);

    void eraseComment(std::string &str);
    std::vector<std::string> splitLine(std::string &line);
};

#endif