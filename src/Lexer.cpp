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

void Lexer::handle(int ac, char const **av) {
    switch (ac) {
        case 1:
            handleConsole();
            break;
        case 2:
            handleFile(av[1]);
            break;
        default:
            throw Exeptions::WrongArgumentsNumber();
    }
}


// private

void Lexer::handleFile(std::string path) {
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
        }
        stream.close();
    }
}

void Lexer::handleConsole() {
	std::string buff;

	while (true) {
		std::getline(std::cin, buff);
		if (buff == ";;") {
			break;
		}
        eraseComment(buff);
		std::cout << buff << std::endl;
	}
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
