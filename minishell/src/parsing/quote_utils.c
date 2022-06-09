/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:14:50 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/09 19:45:19 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	quote_counter(char *s, char c)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (s[++i])
	{
		if (s[i] == c)
			j++;
	}
	if (j % 2 != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	*remove_char(char *str, char garbage, char keep)
{
	char	*src;
	char	*dst;

	dst = str;
	src = dst;
	while (*src != '\0')
	{
		*dst = *src;
		if (*dst != garbage && *dst + 1 != keep)
			dst++;
		src++;
	}
	*dst = '\0';
	return (dst);
}

char	*remove_dquote_out(char *str)
{
	int		start;
	size_t	end;

	start = 0;
	end = ft_strlen(str) - 1;
	if (quote_counter(str, '\"') != 1)
	{
		if (ft_strchr(str, '\"') 
			&& ft_strchr(str, '\'') == NULL)
			if (str[start] == '\"' && str[end] == '\"')
				str = remove_char(str, '\"', '\'');
	}
	return (str);
}

char	*remove_squote_out(char *str)
{
	int		start;
	size_t	end;

	start = 0;
	end = ft_strlen(str) - 1;
	if (quote_counter(str, '\'') != 1)
	{
		if (ft_strchr(str, '\'') 
			&& ft_strchr(str, '\"') == NULL)
			if (str[start] == '\'' && str[end] == '\'')
				str = remove_char(str, '\'', '\"');	
	}
	return (str);
}


void	cmd_parsing(t_shell *shell, int cmd_index)
{
	int		i;

	i = 0;
	while (shell->cmd[cmd_index]->args[i])
	{

		remove_dquote_out(shell->cmd[cmd_index]->args[i]);
		remove_squote_out(shell->cmd[cmd_index]->args[i]);
		i++;
	}
}
