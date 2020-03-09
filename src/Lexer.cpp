#include "Lexer.hpp"


// canonical scope

Lexer::Lexer() {
	this->errors = 0;
}

Lexer::~Lexer() {}

Lexer::Lexer(Lexer const &obj) {
	*this = obj;
}

Lexer &Lexer::operator=(Lexer const &obj) {
	this->errors = obj.errors;
	return (*this);
}


// public

int findNotFlagIndex(int ac, char const **av) {
	for (int i = 1; i < ac; i++) {
		std::string arg = av[i];
		if (arg != "-d")
			return i;
	}
	return 1;
};

void Lexer::handle(int ac, char const **av, code_t &code, bool debug) {
	this->debug = debug;

	if (this->debug)
    	std::cout << "\e[36;1m[ lexer ]\e[0m : lexer handling phase" << std::endl;

	switch (ac) {
		case 1:
			handleConsole(code);
			break;
		case 2:
			if (this->debug) {
				handleConsole(code);
			} else {
				handleFile(av[1], code);
			}
			break;
		case 3:
			if (this->debug) {
				int nfi = findNotFlagIndex(ac, av);
				handleFile(av[nfi], code);
			} else {
				handleFile(av[1], code);
			}
			break;
		default:
			throw Exeptions::WrongArgumentsNumber();
	}
}


// private

void Lexer::handleFile(std::string path, code_t &code) {
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
			CodeLine line;

			i++;
			line.number = i;

			if (!buff.empty() && buff[0] != ';') {

				eraseComment(buff);
				auto tokens = splitLine(buff);

				bool isValid = false;
				size_t size;
				try {
					std::tie(isValid, size) = checkGrammar(tokens);
				}
				catch(const std::exception& e)
				{
					std::stringstream stringstream;
					stringstream << " \e[32;1mline " << line.number << "\e[0m : lexical \e[31;1merror\e[0m : " << e.what();
					line.writeError(stringstream.str());
					this->errors++;
				}

				if (isValid) {
						line.instruction = INSTRUCTION;
					if (size == 2)
						line.value = VALUE;
				}

				code.push_back(line);
			}
		}
		stream.close();
	}
}

void printTokens(tokens_t &tokens) {
	std::cout << tokens.size() << std::endl;
	for (auto token : tokens) {
		std::cout << token << std::endl;
	}
}

void Lexer::handleConsole(code_t &code) {
	std::string buff;

	size_t i = 0;
	while (true) {
		CodeLine line;

		i++;
		line.number = i;

		std::getline(std::cin, buff);
		if (buff == ";;")
			break;

		if (!buff.empty() && buff[0] != ';') {
			eraseComment(buff);
			auto tokens = splitLine(buff);

			bool isValid = false;
			size_t size;
			try {
				std::tie(isValid, size) = checkGrammar(tokens);
			}
			catch(const std::exception& e)
			{
				std::stringstream stringstream;
				stringstream << " \e[32;1mline " << line.number << "\e[0m : lexical \e[31;1merror\e[0m : " << e.what();
				line.writeError(stringstream.str());
				this->errors++;
			}

			if (isValid) {
					line.instruction = INSTRUCTION;
				if (size == 2)
					line.value = VALUE;
			}

			code.push_back(line);
		}
	}
}

std::pair<bool, size_t> Lexer::checkGrammar(tokens_t &tokens) {
	size_t size = tokens.size();
	std::pair<bool, size_t> res = std::make_pair(false, size);

	if (size > 2) {
		throw Exeptions::InvalidExpression();
	}
	else if (size == 2) {
		res.first = checkInstructionWithValue(tokens);
	} else if (size == 1) {
		res.first = checkInstruction(tokens);
	}
	return res;
}

bool Lexer::checkInstruction(tokens_t &tokens) {
	bool res = true;

	std::regex instructions("^(push|assert|pop|dump|add|sub|mul|div|mod|print|exit)");
	if (!regex_match(INSTRUCTION, instructions)) {
		res = false;
		throw Exeptions::InvalidInstraction();
	}

	std::regex instructionsWithValue("^(push|assert)");
	if (regex_match(INSTRUCTION, instructionsWithValue)) {
		res = false;
		throw Exeptions::MissingInstructionValue();
	}

	return res;
}

bool Lexer::checkInstructionWithValue(tokens_t &tokens) {
	bool res = true;

	std::regex instructions("^(push|assert)");
	if (!regex_match(INSTRUCTION, instructions)) {
		res = false;
		throw Exeptions::InvalidInstraction();
	}

	std::regex values(R"(^(int8|int16|int32)[(][-]?\d+[)]|^(float|double)[(][-]?\d+(\.[0-9]+)[)])");
	if (!regex_match(VALUE, values)) {
		res = false;
		throw Exeptions::InvalidValue();
	}

	return res;
}

void Lexer::eraseComment(std::string &str) {
	size_t pos = str.find(";");
	if (pos != std::string::npos) {
		str.erase(pos);
	}
}

tokens_t Lexer::splitLine(std::string &line) {
	std::istringstream tokenStream(line);
	auto first = std::istream_iterator<std::string>{tokenStream};
	auto last = std::istream_iterator<std::string>();
	tokens_t tokens(first, last);
	return tokens;
}