# COLORS
GREEN	= \033[0;32m
RED 	= \033[0;31m
ORANGE	= \033[0;33m
CYAN	= \033[0;36m
RESET	= \033[0m

NAME	= minishell

CC		= cc
CFLAGS	= -Wall -Wextra -Werror
CFLAGS += -g3

#################################################################
# READLINE														#
# Install command: brew install readline						#
# Find where the package is installed: brew info readline		#
#################################################################

RL_V	:= $(shell brew list --versions  readline | sed 's/.*[[:blank:]]//')
RL_P	:= $(shell brew --cellar readline)
RL		= $(RL_P)/$(RL_V)
LIBS	= -L $(RL)/lib/ -lreadline -lhistory

# READLINE BACKUP
#RL		= ../doc/readline/8.1.2
#LIBS	= -L $(RL)/lib/ -lreadline

INC		= -I. -I $(RL)/include/

RM		=	rm -rf

FOLDER	=	src/

FILES	=	main.c \
			init_utils.c \
			res/utils.c \
			res/utils_2.c \
			res/free.c \
			res/ascii.c \
			parsing/pars_args.c \
			parsing/pars_remove.c \
			parsing/pars_single.c \
			parsing/pars_space_2.c \
			parsing/pars_space.c \
			parsing/quote_utils_2.c \
			parsing/quote_utils.c \
			parsing/replace_args.c \
			builtins/env.c \
			builtins/cd.c \
			builtins/echo.c \
			builtins/export.c \
			builtins/pwd.c \
			builtins/unset.c \
			builtins/exit.c \
			builtins/utils/env_utils.c \
			builtins/utils/env_var.c \
			builtins/utils/init_func.c \
			redirection/redirection.c \
			redirection/heredoc.c \
			redirection/utils.c \
			redirection/redi_args.c \
			redirection/redinput.c \
			pipe/pipe.c \
			pipe/pipe_utils.c \
			path/path.c \
			path/path_utils.c \
			signals/ctrl.c \
			signals/signals_utils.c

SRC 	=	$(addprefix $(FOLDER), $(FILES))
OBJ 	=	$(SRC:.c=.o)

LIBFT 	= 	./newlibft/libft.a

all: $(NAME)

.c.o:
	@$(CC) -c $(CFLAGS) $(INC) $< -o $@

$(NAME): $(OBJ)
	@$(MAKE) -C ./newlibft
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME) $(LIBFT)
	@echo "[$(ORANGE)$(NAME)$(RESET)] Creation *.o files & compilation : $(GREEN)OK$(RESET)"
	@echo "[\033[1;32msuccess$(RESET)]: $(NAME) is ready"

debug: $(OBJ)
	@$(MAKE) -C ./newlibft
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)  $(LIBFT)  -fsanitize=address -g
	@echo "[$(ORANGE)$(NAME)$(RESET)] Creation *.o files & compilation : $(GREEN)OK$(RESET)"
	@echo "[\033[1;32msuccess$(RESET)]: Debug $(NAME) is ready"

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