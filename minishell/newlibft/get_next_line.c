/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaquier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 14:54:52 by tpaquier          #+#    #+#             */
/*   Updated: 2021/11/02 14:54:55 by tpaquier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*mem;
	size_t	i;

	i = 0;
	mem = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + 1));
	if (!mem)
		return (NULL);
	while (s1[i])
	{
		mem[i] = s1[i];
		i++;
	}
	mem[i] = '\0';
	return (mem);
}

char	*get_strjoin(char *mem, char *buff)
{
	char	*swap;

	swap = ft_strjoin(mem, buff);
	free(mem);
	return (swap);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem;

	mem = malloc(count * size);
	if (!mem)
		return (NULL);
	return (mem);
}

int	get_back_n(char *mem)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (mem[i])
	{
		if (mem[i] == '\n')
			j = 1;
		i++;
	}
	return (j);
}

char	*get_next_line(int fd)
{
	static char	*mem;
	char		*resul;

	resul = NULL;
	if (BUFFER_SIZE == 0 || (read(fd, NULL, BUFFER_SIZE) == 0 && !mem)
		|| fd < 0)
		return (NULL);
	mem = get_file_for_resul(fd, 1, mem, 0);
	if (mem != NULL)
	{
		resul = get_resul(mem);
		mem = get_newmem(mem, 0, 0);
	}
	return (resul);
}
