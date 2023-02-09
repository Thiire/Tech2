##
## EPITECH PROJECT, 2020
## CNA_trade_2019
## File description:
## Makefile
##

CC = g++

SRCS = 	bot.cpp \
		main.cpp \

OBJS = $(SRCS:.cpp=.o)

CFLAGS =	-W -Wall -Wextra -g3

NAME = trade

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all re