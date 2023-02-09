##
## EPITECH PROJECT, 2020
## Visual Studio Live Share (Workspace)
## File description:
## Makefile
##

CC = g++

SRCS = 	main.cpp \
		Recep.cpp \
		Pizza.cpp \
		Pipe.cpp \
		SafeQueue.cpp \
		Cook.cpp \
		Kitchen.cpp \

OBJS = $(SRCS:.cpp=.o)

CFLAGS = -std=c++11 -w -g3 -pthread

NAME = plazza

all: $(NAME)

graphic:
	make -C bonus/

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	make clean -C bonus/
	rm -rf $(OBJS)

fclean: clean
	make fclean -C bonus/
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean all re