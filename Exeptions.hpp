//
// Created by Dmitry ZABROTSKY on 2019-03-01.
//

#ifndef EXEPTIONS_HPP
#define EXEPTIONS_HPP

#include <exception>

class Exeptions {

public:
    class WrongArgumentsNumber : public std::exception {
    	public:
    		const char *what() const throw();
    };
    class WrongFilePath : public std::exception {
    	public:
			const char *what() const throw();
    };
	class EmptyFile : public std::exception {
		public:
			const char *what() const throw();
	};
};

#endif
