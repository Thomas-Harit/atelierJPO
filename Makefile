##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## my_ftp
##

NAME		=		game

SRC			=		src/main.cpp \

OBJ			=	    $(SRC:.c=.o)

CFLAGS		=		-W -Werror -Wall -Wextra -g

CPPFLAGS	=		-I./include

SFML		=		-lsfml-window -lsfml-system -lsfml-graphics

all:	    $(NAME)

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ) $(CFLAGS) $(CPPFLAGS) $(SFML)

clean:
	rm -f $(OBJ)
	find . -name *~ -delete
	find . -name *#* -delete
	rm -rf *.gcda
	rm -rf *.gcno

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

