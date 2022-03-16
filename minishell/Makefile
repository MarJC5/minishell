# COLORS
GREEN	= \033[0;32m
RED 	= \033[0;31m
ORANGE	= \033[0;33m
CYAN	= \033[0;36m
RESET	= \033[0m

NAME	=	minishell

CC		=	cc
FLAGS	=	-Wall -Wextra -Werror
LIBS	= -lreadline -lncurses

RM		=	rm -rf

FOLDER	=	src/

FILES	=	main.c \
			init_utils.c \
			res/utils.c \
			res/free.c \
			builtins/env_utils.c \
			builtins/env.c \
			builtins/export.c \
			builtins/pwd.c \
			builtins/unset.c \
			signals/sig_utils.c \
			signals/ctrl_c.c

SRC 	=	$(addprefix $(FOLDER), $(FILES))
OBJ 	=	$(SRC:.c=.o)

LIBFT 	= ./newlibft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C ./newlibft
	@$(CC) $(CFLAGS) $(LIBS) -o $(NAME) $(OBJ) $(LIBFT)
	@echo "[$(ORANGE)$(NAME)$(RESET)] Creation *.o files & compilation : $(GREEN)OK$(RESET)"
	@echo "[\033[1;32msuccess$(RESET)]: $(NAME) is ready"

clean:
	@$(MAKE) -C ./newlibft clean
	@$(RM) $(OBJ)
	@echo "[$(ORANGE)$(NAME)$(RESET)] clean *.o files : $(GREEN)OK$(RESET)"

fclean: clean
	@$(MAKE) -C ./newlibft fclean
	@$(RM) $(NAME)
	@echo "[$(ORANGE)$(NAME)$(RESET)] fclean: $(GREEN)OK$(RESET)"

re: fclean all

.PHONY: all clean fclean re