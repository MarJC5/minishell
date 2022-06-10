/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:14:50 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/10 07:16:50 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*remove_char(char *str, int start, int end);

int	ft_strchr_pos(const char *str, int c)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == (char)c)
			return (i);
		i++;
	}
	return (0);
}

int	ft_strrchr_pos(const char *str, int c)
{
	size_t	i;

	i = ft_strlen(str);
	while (i)
	{
		if (str[i] == (char)c)
			return (i);
		i--;
	}
	return (0);
}

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

char	*remove_quote_out(char *str, char c)
{
	int	start;
	int	end;

	start = ft_strchr_pos(str, c);
	end = ft_strrchr_pos(str, c);
	if (str[start] == c && str[end] == c)
		str = remove_char(str, start, end);
	return (str);
}

char	*remove_quote_in(char *str, char c)
{
	int	start;
	int	end;

	start = ft_strchr_pos(str, c);
	end = ft_strrchr_pos(str, c);
	if (str[start] == c && str[end] == c && quote_counter(str, c))
		str = remove_char(str, start, end);
	return (str);
}

char	*remove_char(char *str, int start, int end)
{
	char	*src;
	char	*dst;
	int		i;

	i = 0;
	dst = str;
	src = dst;
	while (*src != '\0')
	{
		*dst = *src;
		if (i != start && i != end)
			dst++;
		src++;
		i++;
	}
	*dst = '\0';
	return (dst);
}


void	cmd_parsing(t_shell *shell, int cmd_index)
{
	int		i;
	size_t	end;

	i = 0;
	end = ft_strlen(shell->cmd[cmd_index]->args[i]) - 1;
	if (shell->cmd[cmd_index]->args[i][0] == '\"'
		&& shell->cmd[cmd_index]->args[i][end] == '\"')
	{
		if (quote_counter(shell->cmd[cmd_index]->args[i], '\"') == 0)
			while (ft_strchr(shell->cmd[cmd_index]->args[i], '\"'))
				remove_quote_out(shell->cmd[cmd_index]->args[i], '\"');
	}
	else if (shell->cmd[cmd_index]->args[i][0] == '\''
		&& shell->cmd[cmd_index]->args[i][end] == '\'')
	{
		if (quote_counter(shell->cmd[cmd_index]->args[i], '\'') == 0)
			while (ft_strchr(shell->cmd[cmd_index]->args[i], '\''))
				remove_quote_out(shell->cmd[cmd_index]->args[i], '\'');
	}
	while (shell->cmd[cmd_index]->args[++i])
	{
		//remove_quote_in(shell->cmd[cmd_index]->args[i], '\"');
		//remove_quote_in(shell->cmd[cmd_index]->args[i], '\'');
		i++;
	}
}
