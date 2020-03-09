CC = g++ -std=c++14 -I incl
CFLAGS = -Wall -Wextra -Werror
NAME = avm
SRC = main.cpp Lexer.cpp Exeptions.cpp CodeLine.cpp Factory.cpp Parser.cpp
OBJ = $(addprefix src/, $(SRC:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all