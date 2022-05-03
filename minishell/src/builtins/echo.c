/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:47:54 by jmartin           #+#    #+#             */
/*   Updated: 2022/05/03 19:33:12 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	isp(char **str, int i, int ret)
{
	int	j;

	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '|' || str[i][j] == '>')
			{
				if (ret == 1)
					return (j);
				if (ret == 0)
					return (i);
			}
			j++;
		}
		i++;
	}
	if (ret == 1)
		return (0);
	else
		return (i);
}

static char	*echo_struct(char **args, int i, int j, int c)
{
	char	*str;
	int		fi;
	size_t	fj;

	fi = isp(args, i, 0);
	fj = isp(args, i, 1);
	while (i < fi)
		c += ft_strlen(args[i++]);
	c += fj;
	str = ft_calloc(c + 2 + (i - 2), 1);
	fj = 0;
	i = 0;
	while (c-- > 0)
	{
		str[i++] = args[j][fj++];
		if (fj >= ft_strlen(args[j]))
		{
			j++;
			fj = 0;
			str[i++] = ' ';
		}
	}
	str[i] = '\0';
	return (str);
}

static void	cr_arg_realloc(char **args, char *newval, int i)
{
	ft_free_tab(args[i]);
	args[i] = newval;
}

static void	cr_arg(t_shell *shell, char **args, int j)
{
	char	*str;
	int		i;

	while (args[j])
	{
		if (ft_strchr(args[j], '$') > 0)
		{
			i = 0;
			while (args[j][i++] != '$')
				;
			if (args[j][i] == '?')
				cr_arg_realloc(args, ft_itoa(g_exit_stat), j);
			else if (args[j][i + 1] != '\0')
			{
				str = get_env_var(shell, args[j]);
				if (!str)
					cr_arg_realloc(args, ft_substr(args[j], 0, (i - 1)), j);
				else
					cr_arg_realloc(args,
						ft_strjoin(ft_substr(args[j], 0, (i - 1)), str), j);
				ft_free_tab(str);
			}
		}
		j++;
	}
}

void	ft_echo(t_shell *shell, int cmd_index)
{
	char	*str;
	int		i;

	shell->bcklash_n = 0;
	if (shell->cmd[cmd_index]->args[1])
	{
		if (shell->cmd[cmd_index]->args[1][0] == '-'
			&& shell->cmd[cmd_index]->args[1][1] == 'n')
			i = 2;
		else
			i = 1;
		if (shell->ispipe >= 1 || shell->redi >= 1)
			redirection(shell, shell->cmd[cmd_index]->args);
		cr_arg(shell, shell->cmd[cmd_index]->args, i);
		str = echo_struct(shell->cmd[cmd_index]->args, i, i, 0);
		write(shell->fd, str, ft_strlen(str));
		free(str);
		if (i == 1)
			write(shell->fd, "\n", 1);
		dup2(1, shell->fd);
	}
	else
		write(shell->fd, "\n", 1);
	g_exit_stat = 0;
}
