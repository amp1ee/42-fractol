NAME		= fractol
CC			= gcc
SRCDIR		= ./src/
SRC			= $(addprefix $(SRCDIR), \
					main.c \
					controls.c)
OBJDIR		= ./obj/
OBJ			= $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)
FLAGS		= -Wall -Wextra -Werror -O3
MLXDIR		= ./minilibx
MLXLIB		= libmlx.a
MLX			= -lmlx -L$(MLXDIR)

ifeq ($(shell uname -s), Linux)
  MLX		+= -lX11 -lXext
else
  MLX		+= -framework OpenGL -framework AppKit
endif

LIBFT		= -lft -L../libft
MULTHREAD	= -pthread
MATHLIB		= -lm
INCL		= fractol.h

.PHONY: all clean fclean re

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCL)
	@mkdir -p $(OBJDIR)
	gcc $(FLAGS) -c $< -o $@ -I.

$(NAME): $(OBJ) $(MLXDIR)/$(MLXLIB)
	gcc $(OBJ) -o $(NAME) $(MLX) $(MATHLIB) $(MULTHREAD) $(LIBFT)
$(MLXLIB):
	@printf "Compiling libmlx.a\n"
	@make -sC $(MLXDIR)
clean:
	rm -rf $(OBJDIR)
fclean: clean
	rm -f $(NAME)

re: fclean all
