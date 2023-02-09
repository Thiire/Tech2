##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

SRC =	strlen.asm \
		strchr.asm \
		memset.asm \
		memcpy.asm \
		memmove.asm \
		strcmp.asm \
		strncmp.asm \
		rindex.asm \
		strstr.asm \
		strpbrk.asm \
		strcspn.asm


ASM =	nasm

OBJ =	$(SRC:.asm=.o)

NASMFLAGS =	-f elf64

LDFLAGS = -shared -fPIC

NAME =	libasm.so

all: $(NAME)

$(NAME):	$(OBJ)
		$(LD) $(LDFLAGS) $(OBJ) -o libasm.so
%.o: %.asm
		$(ASM) $(NASMFLAGS) -o $@ $<

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

test: re
		gcc main.c $(OBJ) -g3
