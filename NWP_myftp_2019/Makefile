##
## EPITECH PROJECT, 2020
## NWP_myftp_2019
## File description:
## Makefile
##

CC = gcc

SRCS =	main.c \
		return.c \
		init.c \
		server.c \

OBJS = $(SRCS:.c=.o)

CFLAGS =	-W -Wall -Wextra -g3

NAME = myftp

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all re
