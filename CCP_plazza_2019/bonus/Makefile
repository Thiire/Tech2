##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

CC = g++

SRCS =	Main.cpp	\
		Graphic.cpp	\
		Recep2.cpp	\
		../Pizza.cpp	\
		../Pipe.cpp	\
		../SafeQueue.cpp	\
		../Cook.cpp	\
		../Kitchen.cpp	\

ALFLAGS	=	`pkg-config --libs allegro-5 allegro_font-5 allegro_image-5 allegro_ttf-5 allegro_dialog-5 allegro_main-5 allegro_primitives-5`

CFLAGS =	-std=c++11 -w -g3 -pthread -w -g3

NAME = ./plazza_bonus

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(ALFLAGS)

clean:
	rm -f *.o

fclean:	clean
		rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re