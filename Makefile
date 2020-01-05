################################################################################
#                                                                              #
#                                Makefile                                      #
#                                                                              #
################################################################################

NAME	= Index

SRCPATH	=	src/

SRC 	= 	$(SRCPATH)main.c			\
			$(SRCPATH)error.c			\
			$(SRCPATH)index.c			\
			$(SRCPATH)parsing.c			\
			$(SRCPATH)ft_base.c 		\
			$(SRCPATH)lst.c				\
			$(SRCPATH)hachage.c			\
			$(SRCPATH)fonctionnalite.c	\
			$(SRCPATH)menu.c			\

OBJ 	= $(SRC:.c=.o)

FLAGS	=	-Wall	\
			-Werror	\
			-ansi	\
			-lm		\

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

1: all clean

re: fclean all
