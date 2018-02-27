NAME		= fractol
CC			= gcc
SRCDIR		= ./src/
SRC			= $(addprefix $(SRCDIR), \
					main.c \
					controls.c \
					draw.c \
					functions.c \
					functions2.c \
					complex.c \
					complex2.c \
					colors.c)
OBJDIR		= ./obj/
OBJ			= $(SRC:$(SRCDIR)%.c=$(OBJDIR)%.o)
FLAGS		= -Wall -Wextra -Werror -O3

MLX			= -lmlx
ifeq ($(shell uname -s), Linux)
  MLXDIR	= ./minilibx/
  MLX		+= -lX11 -lXext -L$(MLXDIR)
  MLXLIB	= $(addprefix $(MLXDIR), libmlx.a)
  MULTHREAD	= -pthread
else
  MLX		+= -framework OpenGL -framework AppKit
endif

LIBFT_DIR	= ./libft/
LIBFT		= $(addprefix $(LIBFT_DIR), libft.a)
LIBFT_FLAGS	= -lft -L$(LIBFT_DIR)
MATHLIB		= -lm
INCL		= fractol.h complex.h

.PHONY: all clean fclean re

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCL)
	@printf "\tCompiling $<\n"
	@mkdir -p $(OBJDIR)
	@gcc $(FLAGS) -c $< -o $@ -I.

$(NAME): $(OBJ) $(LIBFT) $(MLXLIB)
	@gcc $(OBJ) -o $(NAME) $(MLX) $(MATHLIB) $(MULTHREAD) $(LIBFT_FLAGS)
	@printf "Done\n"
$(LIBFT):
	@printf "\tCompiling libft.a...\n"
	@make -sC $(LIBFT_DIR)
$(MLXLIB):
	@printf "\tCompiling libmlx.a\n"
	@make -sC $(MLXDIR)
clean:
	@rm -rf $(OBJDIR)
	@printf "\tObject files removed\n"
fclean: clean
	@rm -f $(NAME)
	@printf "\tExecutable '$(NAME)' removed\n"
re: fclean all
