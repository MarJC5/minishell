/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 01:50:22 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/12 23:56:33 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	pipe_tester(t_shell *shell, char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (count == 1 && str[i] != 32 && str[i] != '|')
			count = 0;
		if (str[i] == '|')
		{
			if (count == 1)
			{
				str_err("minishell: syntax error near unexpected token `|'",
					NULL);
				shell->err_quote = 1;
				shell->err_pipe = 1;
				free(str);
				return (1);
			}
			count = 1;
		}
		i++;
	}
	return (0);
}

void	ft_free_tab(char *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	ft_free_multi_tab(char **ptr)
{
	int	i;

	i = (args_counter(ptr) - 1);
	while (i >= 0)
		ft_free_tab(ptr[i--]);
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	ft_free_read_args(t_shell *shell, char *line)
{
	int	i;

	i = 0;
	if (shell->err_pipe == 1)
	{
		shell->err_pipe = 0;
		free(line);
	}
	else
	{
		while (i < shell->cmd_count)
			ft_free_multi_tab(shell->cmd[i++]->args);
		i = 0;
		while (i < shell->cmd_count)
		{
			free(shell->cmd[i]->name);
			free(shell->cmd[i++]);
		}
		if (line)
			free(line);
		if (shell->cmd)
			free(shell->cmd);
	}
}
