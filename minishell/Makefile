# COLORS
GREEN	= \033[1;32m
RED 	= \033[1;31m
ORANGE	= \033[1;33m
RESET	= \033[0m

NAME	=	minishell

CC		=	cc
FLAGS	=	-Wall -Wextra -Werror

RM		=	rm -rf

FOLDER	=	src/

FILES	=	main.c \

SRC 	=	$(addprefix $(FOLDER), $(FILES))
OBJ 	=	$(SRC:.c=.o)

LIBFT = ./newlibft/libft.a

all: $(OBJ)
	@$(MAKE) -C ./newlibft
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)
	@echo "[$(GREEN)created$(RESET)]: $(NAME)"

clean:
	@$(MAKE) -C ./newlibft clean
	@$(RM) $(OBJ)
	@echo "[$(RED)deleted$(RESET)]: *.o files"

fclean: clean
	@$(MAKE) -C ./newlibft fclean
	@$(RM) $(NAME)
	@echo "[$(RED)deleted$(RESET)]: $(NAME)"

re: fclean all

.PHONY: all clean fclean re