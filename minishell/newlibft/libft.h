/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaquier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:18:47 by tpaquier          #+#    #+#             */
/*   Updated: 2021/10/20 09:20:35 by tpaquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	42
# endif

# include <stdarg.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

int		ft_atoi(const char *str);

void	ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t nmemb, size_t size);

void	ft_putnbr_fd(int n, int fd);

char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_strtrim(char const *s1, char const *set);

char	*ft_itoa(int n);

char	**ft_split(char const *s, char c);

char	*ft_strjoin(char const *s1, char const *s2);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void	ft_putchar_fd(char c, int fd);

void	ft_putendl_fd(char *s, int fd);

void	ft_putstr_fd(char *s, int fd);

int		ft_isalnum(int alnum);

char	*ft_strdup(const char *s);

int		ft_isalpha(int alpha);

int		ft_isascii(int ascii);

int		ft_isdigit(int digit);

int		ft_isprint(int print);

void	*ft_memchr(const void *s, int c, size_t n);

void	ft_striteri(char *s, void (*f)(unsigned int, char *));

int		ft_memcmp(const void *b1, const void *b2, size_t len);

void	*ft_memcpy(void *dst, const void *src, size_t n);

void	*ft_memmove(void *dst, const void *src, size_t len);

void	*ft_memset(void *p, int c, size_t len);

char	*ft_strchr(const char *s, int c);

size_t	ft_strlcat(char *dst, const char *src, size_t ds);

size_t	ft_strlcpy(char *dst, const char *src, size_t ds);

size_t	ft_strlen(const char *str);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_strnstr(const char *h, const char *n, size_t len);

char	*ft_strrchr(const char *s, int c);

int		ft_tolower(int c);

int		ft_toupper(int c);

int		ft_printf(const char *str, ...);

void	ft_put_unsigned_nbr_fd(unsigned int n, int fd);

void	ft_putstr_two_fd(char *s, int fd, int *byte);

int		ft_hexconverter_ptr(unsigned long dec, int *byte);

int		ft_hexconverter(unsigned int dec);

int		ft_hexconverter_min(unsigned int dec);

int		ft_hex_a(va_list arg, int b);

int		ft_nbr_u(va_list arg, int b);

int		ft_hex_b(va_list arg, int b);

int		ft_char_c(va_list arg, int b);

int		ft_char_s(va_list arg, int b, int *byte);

int		ft_hex_p(void *a, int b, int *byte);

int		ft_nbr_di(va_list arg, int b);

char	*get_next_line(int fd);

char	*get_strjoin(char *mem, char *buff);

size_t	ft_strlen(const char *str);

char	*ft_strdup(const char *s1);

int		get_back_n(char *mem);

char	*ft_strjoin(char const *s1, char const *s2);

char	*get_file_for_resul(int fd, int taille, char *mem, int n);

char	*get_resul(char *mem);

void	*ft_calloc(size_t count, size_t size);

char	*get_newmem(char *mem, int j, int i);

#endif
