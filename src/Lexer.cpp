#include "Lexer.hpp"


// canonical scope

Lexer::Lexer() {}

Lexer::~Lexer() {}

Lexer::Lexer(Lexer const &obj) {
    *this = obj;
}

Lexer &Lexer::operator=(Lexer const &obj) {
    this->errors = obj.errors;
    return (*this);
}


// public

void Lexer::handle(int ac, char const **av, std::vector<CodeLine> &code) {
    switch (ac) {
        case 1:
            handleConsole(code);
            break;
        case 2:
            handleFile(av[1], code);
            break;
        default:
            throw Exeptions::WrongArgumentsNumber();
    }
}


// private

void Lexer::handleFile(std::string path, std::vector<CodeLine> &code) {
    std::ifstream stream(path);

    if (!stream.is_open()) {
        throw Exeptions::WrongFilePath();
    }
    else if (stream.peek() == std::ifstream::traits_type::eof()) {
        throw Exeptions::EmptyFile();
    }
    else {
        std::string buff;
		size_t i = 0;
        while (std::getline(stream, buff))
        {
        	i++;
        	if (!buff.empty() && buff[0] != ';') {
				if (verifyString(buff, i)) {
					std::cout << buff;
					if (!stream.eof())
						std::cout << "\n";
				}
			}

            eraseComment(buff);
            std::cout << "with out comment: " << buff << std::endl;
            
            auto tokens = splitLine(buff);

            if (checkGrammar(tokens)) {
                std::cout << "profit." << code.size() << std::endl;
            }

        }
        stream.close();
    }
}

void Lexer::handleConsole(std::vector<CodeLine> &code) {
	std::string buff;

	while (true) {
		std::getline(std::cin, buff);
		if (buff == ";;") {
			break;
		}
        if (!buff.empty() && buff[0] != ';') {
            eraseComment(buff);
            std::cout << "with out comment: " << buff << std::endl;
            
            auto tokens = splitLine(buff);

            if (checkGrammar(tokens)) {
                std::cout << "profit." << code.size() << std::endl;
            }

            // std::cout << tokens.size() << std::endl;        
            // for (auto token : tokens) {
            // 	std::cout << token << std::endl;        
            // }
        }
	}
}

bool Lexer::checkGrammar(std::vector<std::string> &tokens) {
    bool res = false;
    size_t size = tokens.size();
    
    if (size > 2) {
        throw Exeptions::InvalidExpression();
    }
    else if (size == 2) {
        res = checkInstructionWithValue(tokens);
    } else if (size == 1) {
        res = checkInstruction(tokens);
    }
    return res;
}

bool Lexer::checkInstruction(std::vector<std::string> &tokens) {
	std::regex instructions("^(pop|dump|add|sub|mul|div|mod|print|exit)");	
    
    if (!regex_match(tokens[0], instructions)) {
        throw Exeptions::InvalidInstraction();
	}
	return true;
}

bool Lexer::checkInstructionWithValue(std::vector<std::string> &tokens) {
	std::regex instructions("^(push|assert)");   
    if (!regex_match(tokens[0], instructions)) {
        throw Exeptions::InvalidInstraction();
	}
    
    std::regex values(R"(^(int8|int16|int32)[(][-]?\d+[)]|^(float|double)[(][-]?\d+(.[0-9]+)[)])");
    if (!regex_match(tokens[1], values)) {
        throw Exeptions::InvalidValue();
	}
	return true;
}

bool Lexer::verifyString(std::string str, size_t i) {
	std::regex integers(R"(^(push|assert)[\t ]+(int8|int16|int32)[(][-]?\d+[)][\t ]*(;.*)?$)");
	std::regex floats(R"(^(push|assert)[\t ]+(float|double)[(][-]?\d+(.[0-9]+)[)][\t ]*(;.*)?$)");
	std::regex instructions(R"(^(pop|dump|add|sub|mul|div|mod|print|exit)[\t ]*(;.*)?$)");

	if (!regex_match(str, integers) && !regex_match(str, floats) && !regex_match(str, instructions)) {
		std::cout << i << " ";
		throw Exeptions::CodeError();
	}
	return true;
}

void Lexer::eraseComment(std::string &str) {
    size_t pos = str.find(";");
    if (pos != std::string::npos) {
        str.erase(pos);
    }
}

std::vector<std::string> Lexer::splitLine(std::string &line) {
    std::istringstream tokenStream(line);
    auto first = std::istream_iterator<std::string>{tokenStream};
    auto last = std::istream_iterator<std::string>();
	std::vector<std::string> tokens(first, last);
	return tokens;
}