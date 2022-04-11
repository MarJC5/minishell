# COLORS
GREEN	= \033[0;32m
RED 	= \033[0;31m
ORANGE	= \033[0;33m
CYAN	= \033[0;36m
RESET	= \033[0m

NAME	= minishell

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

#################################################################
# READLINE														#
# Install command: brew install readline						#
# Find where the package is installed: brew info readline		#
#################################################################

# INC	= -I. -I $(HOME)/.brew/Cellar/readline/8.1.2/include/
# LIBS	= -L $(HOME)/.brew/Cellar/readline/8.1.2/lib/ -lreadline

INC		= -I. -I /usr/local/Cellar/readline/8.1.2/include/
LIBS	= -L /usr/local/Cellar/readline/8.1.2/lib/ -lreadline -lhistory

RM		=	rm -rf

FOLDER	=	src/
DIR_OBJ = 	obj/

FILES	=	main.c \
			init_utils.c \
			res/utils.c \
			res/free.c \
			builtins/env.c \
			builtins/cd.c \
			builtins/echo.c \
			builtins/export.c \
			builtins/pwd.c \
			builtins/unset.c \
			builtins/exit.c \
			builtins/utils/env_utils.c \
			builtins/utils/init_func.c \
			redirection/redirection.c \
			redirection/utils.c \
			pipe/pipe.c \
			pipe/utils.c \
			signals/ctrl_c.c \
			signals/utils.c

SRC 	=	$(addprefix $(FOLDER), $(FILES))
OBJ 	=	$(SRC:.c=.o)

LIBFT 	= 	./newlibft/libft.a

all: $(NAME)

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) $(INC)

$(NAME): $(OBJ)
	@$(MAKE) -C ./newlibft
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LIBS) 
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

valgrind:
	valgrind --leak-check=full ./$(NAME)

.PHONY: all clean fclean re valgrind