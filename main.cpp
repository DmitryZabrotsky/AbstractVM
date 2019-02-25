#include <iostream>

int main(int argc, char const *argv[])
{
	if (argc > 2) {
		std::cout << "a lot of arguments!" << std::endl;
		exit(0);
	}
	else {
		std::cout << "say HELLO to " << argv[0] << std::endl;
	}
	return 0;
}