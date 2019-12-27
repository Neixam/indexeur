################################################################################
#                                                                              #
#                                Makefile                                      #
#                                                                              #
################################################################################

NAME	= Index

SRCPATH	=	main.c	\
			error.c	\

SRC 	= src/$(SRCPATH)

OBJ 	= $(SRC:.c=.o)

FLAGS	=	-Wall	\
			-Werror	\
			-ansi	\
			-lMLV	\

HEADER	= includes

all:$(NAME)

$(NAME): $(OBJ)
	gcc $(FLAGS) $^ -o $(NAME) -I $(HEADER)

%.o:%.c
	gcc $(FLAGS) -o $@ -c $^ -I $(HEADER)

clean:
	/bin/rm -rf $(OBJ)

bclean:
	/bin/rm -rf $(NAME)

fclean: clean bclean

re: fclean all