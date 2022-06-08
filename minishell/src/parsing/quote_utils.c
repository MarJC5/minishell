/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 16:14:50 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/08 15:37:14 by jmartin          ###   ########.fr       */
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
	{
		str_err("minishell: ", "syntax error, command not found");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char	*cmd_remove_quote(char *str)
{
	int		start;
	size_t	end;

	start = 0;
	end = ft_strlen(str) - 1;
	if (quote_counter(str, '\"') != 1)
	{
		if (str[start] == '\"' && str[end] == '\"')
			return (ft_substr(str, 1, end - 1));
	}
	if (quote_counter(str, '\'') != 1)
	{
		if (str[start] == '\'' && str[end] == '\'')
			return (ft_substr(str, 1, end - 1));
	}
	return (str);
}

char	*remove_char(char *str, char garbage)
{
	char	*src;
	char	*dst;

	dst = str;
	src = dst;
	while (*src != '\0')
	{
		*dst = *src;
		if (*dst != garbage)
			dst++;
		src++;
	}
	*dst = '\0';
	return (dst);
}

void	cmd_parsing(t_shell *shell, int cmd_index)
{
	int		i;

	i = 1;
	while (shell->cmd[cmd_index]->args[i])
	{
		remove_char(shell->cmd[cmd_index]->args[i], '\\');
		i++;
	}
}
