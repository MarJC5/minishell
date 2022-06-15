/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:47:54 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/15 12:47:36 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	cr_arg_realloc(char **args, char *newval, int i, int j)
{
	char	*begin;
	char	*end;
	char	*tmp;

	begin = NULL;
	end = NULL;
	tmp = NULL;
	ft_free_tab(args[i]);
	if (args[i][j] == '?')
	{
		begin = ft_substr(args[i], 0, (j - 1));
		end = ft_substr(args[i], j + 1, ((int)ft_strlen(begin) - j));
		tmp = ft_strjoin(begin, newval);
		args[i] = ft_strjoin(tmp, end);
		free(begin);
		free(end);
		free(tmp);
	}
	else
		args[i] = newval;
}

static void	echo_return_val(int ret_val, char **args, int j, int i)
{
	char	*ret;

	ret = ft_itoa(ret_val);
	cr_arg_realloc(args, ret, j, i);
	free(ret);
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
				echo_return_val(g_exit_stat, args, j, i);
			else if (args[j][i + 1] != '\0')
			{
				str = get_env_var(shell, args[j]);
				if (!str)
					cr_arg_realloc(args, ft_substr(args[j], 0, (i - 1)), j, i);
				else
					cr_arg_realloc(args,
						ft_strjoin(ft_substr(args[j], 0, (i - 1)), str), j, i);
				ft_free_tab(str);
			}
		}
		j++;
	}
}

static void	echo_write(t_shell *shell, int cmd_index, int j)
{
	size_t	i;
	size_t	end;

	while (shell->cmd[cmd_index]->args[j]
		&& j < shell->cmd[cmd_index]->args_count)
	{
		i = 0;
		end = ft_strlen(shell->cmd[cmd_index]->args[j]);
		while (i < end)
		{
			if (shell->cmd[cmd_index]->args[j][i] == ' '
				&& i == 0)
				i++;
			if (shell->cmd[cmd_index]->args[j][i] != '\"'
				&& (i != 0 || i != end))
				write(1, &shell->cmd[cmd_index]->args[j][i], 1);
			i++;
		}
		if (++j != shell->cmd[cmd_index]->args_count
			&& shell->cmd[cmd_index]->quotted == 0)
			write(1, " ", 1);
	}
}

void	ft_echo(t_shell *shell, int cmd_index)
{
	int		i;
	int		start;

	if (ft_strchr(shell->cmd[cmd_index]->args[0], '-') == NULL)
		start = 1;
	else
		start = 0;
	pars_echo_endl(shell, shell->cmd[cmd_index]->args, cmd_index, start);
	if (shell->cmd[cmd_index]->args[start])
	{
		if (shell->bcklash_n)
		{
			i = 2;
			start += 1;
		}
		else
			i = 1;
		cr_arg(shell, shell->cmd[cmd_index]->args, i);
		echo_write(shell, cmd_index, start);
		if (i == 1)
			write(1, "\n", 1);
	}
	else
		write(1, "\n", 1);
}
