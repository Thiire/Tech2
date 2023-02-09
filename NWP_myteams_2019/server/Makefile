##
## EPITECH PROJECT, 2020
## NWP_myteams_2019
## File description:
## Makefile
##

CC = gcc

SRCS =	main.c \
		init.c	\
		teams.c	\
		utils.c	\
		features/login.c	\
		features/help.c		\
		features/users.c	\
		../parser/enumParser.c	\
		../parser/parser1.c	\
		../parser/parser2.c	\

OBJS = $(SRCS:.c=.o)

CFLAGS =	-W -Wall -Wextra -g3 -luuid

NAME = myteams_server

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all re
