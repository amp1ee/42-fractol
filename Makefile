CC=gcc
SRC=main.c
OBJ=$(SRC:.c=.o)
NAME=fractol
FLAGS=-Wall -Wextra -Werror
MLXFLAGS=-lmlx
ifeq ($(shell uname -s), Linux)
	MLXFLAGS += -lX11 -lXext
else
	MLXFLAGS += -framework OpenGL -framework AppKit
endif
LIBFLAGS=-lft -L../libft -lpthread
MATH=-lm

.PHONY: all clean fclean re

all: $(NAME)

$(OBJ): $(SRC)
	gcc -c $(SRC) -o $(OBJ)

$(NAME): $(OBJ)
	gcc $(OBJ) -o $(NAME) $(MLXFLAGS) $(MATH) $(LIBFLAGS)
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
