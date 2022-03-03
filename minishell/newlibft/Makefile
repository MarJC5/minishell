NAME = libft.a

CFLAGS = -Wall -Werror -Wextra

ARFLAGS = -crs

CC = gcc

RM = rm -f

PNTC = ft_striteri.c ft_strmapi.c ft_itoa.c ft_strcmp.c ft_split.c ft_strtrim.c ft_strjoin.c ft_substr.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_bzero.c ft_isalpha.c ft_isprint.c ft_memcpy.c ft_strchr.c ft_strlcpy.c ft_strnstr.c ft_toupper.c ft_calloc.c ft_isascii.c ft_memchr.c ft_memmove.c ft_strdup.c ft_strlen.c ft_strrchr.c ft_atoi.c ft_isalnum.c ft_isdigit.c ft_memcmp.c ft_memset.c ft_strlcat.c ft_strncmp.c ft_tolower.c ft_printf_utils.c ft_printf.c ft_printf_hex_converters.c get_next_line.c get_next_line_utils.c

PNTO = $(PNTC:.c=.o)

GREEN	= \033[0;32m
ORANGE	= \033[0;33m

NC = \033[0m

all : make

make : $(PNTC)
	@$(CC) $(CFLAG) -c $(PNTC)
	@ar $(ARFLAGS) $(NAME) $(PNTO)
	@echo "[$(ORANGE)libft$(NC)] Creation *.o files & compilation : $(GREEN)OK$(NC)"

clean :
	@/bin/$(RM) $(PNTO)
	@echo "[$(ORANGE)libft$(NC)] clean *.o files : $(GREEN)OK$(NC)"

fclean : clean
	@/bin/$(RM) $(NAME)
	@echo "[$(ORANGE)libft$(NC)] fclean : $(GREEN)OK$(NC)"

re : clean fclean all

.PHONY : all clean fclean re
