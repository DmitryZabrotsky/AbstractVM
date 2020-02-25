#ifndef PARSER_HPP
#define PARSER_HPP

class Parser {
public:

    Parser();
    ~Parser();
    Parser(Parser const &obj);

    Parser &operator=(Parser const &obj);

    void parse(int ac, char const **av);
};

#endif