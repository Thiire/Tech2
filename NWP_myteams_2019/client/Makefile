##
## EPITECH PROJECT, 2020
## NWP_myteams_2019
## File description:
## Makefile
##

CC = gcc

SRCS =	main.c \
		client.c \
		message.c \

OBJS = $(SRCS:.c=.o)

CFLAGS =	-W -Wall -Wextra -g3

NAME = myteams_cli

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all re
