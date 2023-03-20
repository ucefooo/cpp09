NAME =  PmergeMe

SRC = main.cpp PmergeMe.cpp

HD = PmergeMe.hpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(SRC) $(HD)
	c++ -Wall -Wextra -Werror -std=c++98 $(SRC) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all