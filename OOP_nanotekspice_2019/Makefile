##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

CC = g++

SRCS = 	$(wildcard *.cpp) \
		$(wildcard circuit/*.cpp)

OBJS = $(SRCS:.cpp=.o)

CFLAGS = -W -Wall -Wextra -g3

NAME = nano

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all re