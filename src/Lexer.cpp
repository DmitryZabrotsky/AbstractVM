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
				eraseComment(buff);
				std::cout << "with out comment: " << buff << std::endl;

				auto tokens = splitLine(buff);

				if (checkGrammar(tokens).first) {
					std::cout << "profit." << code.size() << std::endl;
				}

				if (!stream.eof())
					std::cout << "\n";
				}
		}
		stream.close();
	}
}

void printTokens(std::vector<std::string> &tokens) {
	std::cout << tokens.size() << std::endl;
	for (auto token : tokens) {
		std::cout << token << std::endl;
	}
}

void Lexer::handleConsole(std::vector<CodeLine> &code) {
	std::string buff;

	size_t i = 0;
	while (true) {
		CodeLine line;

		i++;
		line.number = i;

		std::getline(std::cin, buff);
		if (buff == ";;") {
			break;
		}
		if (!buff.empty() && buff[0] != ';') {
			eraseComment(buff);

			// std::cout << "with out comment: " << buff << std::endl;

			auto tokens = splitLine(buff);

			// printTokens(tokens);

			bool isValid = false;
			size_t size;
			try {
				std::tie(isValid, size) = checkGrammar(tokens);
			}
			catch(const std::exception& e)
			{
				std::stringstream stringstream;
				stringstream << "line: " << line.number << " | lexical error | " << e.what();
				line.writeError(stringstream.str());
				this->errors = true;
			}

			if (isValid) {
				std::cout << "isValid " << code.size() << std::endl;
				if (size == 1) {
					line.operation = tokens[0];
				}
				if (size == 2) {
					line.operation = tokens[0];
					line.value = tokens[1];
				}
			}
		}

		line.printLine();
	}
}

std::pair<bool, size_t> Lexer::checkGrammar(std::vector<std::string> &tokens) {
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

bool Lexer::checkInstruction(std::vector<std::string> &tokens) {
	bool res = true;

	std::regex instructions("^(push|assert|pop|dump|add|sub|mul|div|mod|print|exit)");
	if (!regex_match(tokens[0], instructions)) {
		res = false;
		throw Exeptions::InvalidInstraction();
	}

	std::regex instructionsWithValue("^(push|assert)");
	if (regex_match(tokens[0], instructionsWithValue)) {
		res = false;
		throw Exeptions::MissingInstructionValue();
	}

	return res;
}

bool Lexer::checkInstructionWithValue(std::vector<std::string> &tokens) {
	bool res = true;

	std::regex instructions("^(push|assert)");
	if (!regex_match(tokens[0], instructions)) {
		res = false;
		throw Exeptions::InvalidInstraction();
	}

	std::regex values(R"(^(int8|int16|int32)[(][-]?\d+[)]|^(float|double)[(][-]?\d+(.[0-9]+)[)])");
	if (!regex_match(tokens[1], values)) {
		res = false;
		throw Exeptions::InvalidValue();
	}

	return res;
}

// bool Lexer::verifyString(std::string str, size_t i) {
// 	std::regex integers(R"(^(push|assert)[\t ]+(int8|int16|int32)[(][-]?\d+[)][\t ]*(;.*)?$)");
// 	std::regex floats(R"(^(push|assert)[\t ]+(float|double)[(][-]?\d+(.[0-9]+)[)][\t ]*(;.*)?$)");
// 	std::regex instructions(R"(^(pop|dump|add|sub|mul|div|mod|print|exit)[\t ]*(;.*)?$)");

// 	if (!regex_match(str, integers) && !regex_match(str, floats) && !regex_match(str, instructions)) {
// 		std::cout << i << " ";
// 		throw Exeptions::CodeError();
// 	}
// 	return true;
// }

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