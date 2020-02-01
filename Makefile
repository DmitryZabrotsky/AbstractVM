CC = g++ -std=c++11 -I incl
CFLAGS = -Wall -Wextra -Werror
NAME = avm
SRC = main.cpp Lexer.cpp Exeptions.cpp CodeLine.cpp
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