/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:47:54 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/14 09:46:06 by jmartin          ###   ########.fr       */
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

static void	echo_set_arg(t_shell *shell, int cmd_index, int env_pos, int env_size)
{
	size_t	i;
	size_t	pos;
	size_t	j;
	char	*newval;

	i = 0;
	j = 0;
	pos = ft_strchr_pos(shell->cmd[cmd_index]->pars_dollars, '$');
	newval = ft_strtrim(shell->envp[env_pos] + env_size, "=");
	while (i < shell->cmd[cmd_index]->pars_len)
	{
		shell->cmd[cmd_index]->pars_args[i++] = shell->cmd[cmd_index]->pars_dollars[j++];
		if (i == pos && (shell->cmd[cmd_index]->pars_dollars[j + env_size + 1] == '/'
			|| shell->cmd[cmd_index]->pars_dollars[j + env_size + 1] == ' '))
		{
			pos = j + env_size + 1;
			j = 0;
			while (j < ft_strlen(newval))
			{
				shell->cmd[cmd_index]->pars_args[i] = newval[j];
				i++;
				j++;
			}
			j = pos;
		}
	}
	shell->cmd[cmd_index]->pars_args[i] = '\0';
}

static void	echo_get_arg(t_shell *shell, int cmd_index)
{
	int		i;
	int		j;
	char	*find;

	i = 0;
	find = ft_strchr(shell->cmd[cmd_index]->pars_args, '$') + 1;
	while (shell->envp[i])
	{
		j = 0;
		while (shell->envp[i][j] == find[j])
			j++;
		if (shell->envp[i][j] == '=')
			break ;
		else
			i++;
	}
	shell->cmd[cmd_index]->pars_len = ft_strlen(shell->cmd[cmd_index]->pars_args) + ft_strlen(ft_strtrim(shell->envp[i] + j, "="));
	shell->cmd[cmd_index]->pars_dollars = ft_strdup(shell->cmd[cmd_index]->pars_args);
	free(shell->cmd[cmd_index]->pars_args);
	shell->cmd[cmd_index]->pars_args = malloc(sizeof(char) * shell->cmd[cmd_index]->pars_len + 1);
	echo_set_arg(shell, cmd_index, i, j);
}

static void	echo_write(t_shell *shell, int cmd_index, int j)
{
	if (shell->cmd[cmd_index]->pars_args != NULL)
	{
		echo_get_arg(shell, cmd_index);
		write(1, shell->cmd[cmd_index]->pars_args,
			ft_strlen(shell->cmd[cmd_index]->pars_args));
	}
	else
	{
		while (shell->cmd[cmd_index]->args[j]
			&& j < shell->cmd[cmd_index]->args_count)
		{
			write(1, shell->cmd[cmd_index]->args[j],
				ft_strlen(shell->cmd[cmd_index]->args[j]));
			if (++j != shell->cmd[cmd_index]->args_count)
				write(1, " ", 1);
		}
	}
}

void	ft_echo(t_shell *shell, int cmd_index)
{
	int		i;
	int		j;

	j = 1;
	shell->bcklash_n = 0;
	if (shell->cmd[cmd_index]->args[1])
	{
		if ((shell->cmd[cmd_index]->args[1][0] == '-'
			&& shell->cmd[cmd_index]->args[1][1] == 'n'))
			i = 2;
		else
			i = 1;
		cr_arg(shell, shell->cmd[cmd_index]->args, i);
		echo_write(shell, cmd_index, j);
		if (i == 1)
			write(1, "\n", 1);
	}
	else
		write(1, "\n", 1);
}
