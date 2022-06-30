/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:16:18 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/21 16:55:42 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	old_fd(t_shell *shell)
{
	if (ft_more_redi(shell->cmd[0]->args, '>') == 1)
	{
		str_err("minishell: syntax error near unexpected token `>'", NULL);
		return ;
	}
	shell->fd = dup(STDOUT_FILENO);
	redirection(shell, 0);
	ft_redo_char(shell, 0);
	init_func(shell, 0);
	shell->cmd[0]->func(shell, 0);
	dup2(shell->fd, STDOUT_FILENO);
	close(shell->fd);
}

void	old_fd_two(t_shell *shell)
{
	shell->redinput_err = 0;
	if (ft_more_redi(shell->cmd[0]->args, '<') == 1)
	{
		str_err("minishell: syntax error near unexpected token `<'", NULL);
		return ;
	}
	shell->fd_in = dup(STDIN_FILENO);
	if (isdoubleredi(shell->cmd[0]->args, '<') == 2)
		heredoc(shell, 0);
	else if (redirection_input(shell, 0) == 1)
		return ;
	if (shell->redi >= 1)
		old_fd(shell);
	else if (shell->redinput_err == 0)
	{
		ft_redo_char(shell, 0);
		init_func(shell, 0);
		shell->cmd[0]->func(shell, 0);
	}
	if (shell->cmd[0]->heredoc == 1)
		unlink("temp_minishell");
	shell->cmd[0]->heredoc = 0;
	shell->redinput_err = 0;
	dup2(shell->fd_in, STDIN_FILENO);
	close(shell->fd_in);
}

static void	split_pipe_cmd(t_shell *shell, char *args)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(args, '|');
	while (tmp[i])
	{
		if (ft_isspace(tmp[i]))
		{
			pars_args(shell, tmp[i], i);
			init_func(shell, i);
			shell->cmd[i]->start = 1;
		}
		i++;
	}
	ft_free_multi_tab(tmp);
}

void	init_cmd(t_shell *shell, char *args)
{
	int	j;

	replace_spec_char(args, 0, 0, '\0');
	shell->redinput = ft_strchr(args, '<');
	is_pipe(args, shell);
	if (shell->ispipe >= 1)
		j = ++shell->ispipe;
	else
		j = 1;
	shell->cmd = malloc(j * sizeof(t_cmd));
	if (!shell->cmd)
		return ;
	if (j == 1 && ft_isspace(args))
	{
		pars_args(shell, args, 0);
		init_func(shell, 0);
		shell->cmd[0]->start = 1;
	}
	else if (j > 1)
		split_pipe_cmd(shell, args);
	ft_free_tab(args);
}

char	*init_read(t_shell *shell)
{
	char	*details;
	char	*prompt;
	char	*join_d;
	char	*join_p;

	join_d = ft_strjoin("\033[0m:", ft_strrchr(shell->current_path, '/') + 1);
	if (ft_strcmp(shell->current_path, getenv("HOME")) == 0
		|| ft_strcmp(shell->current_path, "/") == 0)
		details = ft_strdup("\033[0m:~");
	else
		details = ft_strjoin(getenv("USER"), join_d);
	join_p = ft_strjoin(details, " $ ");
	prompt = ft_strjoin("\033[1;36mminishell\033[1;37m@\033[1;32m", join_p);
	ft_free_tab(details);
	ft_free_tab(join_d);
	ft_free_tab(join_p);
	ft_free_tab(prompt);
	return (readline(
			"\033[1;36mminishell\033[1;37m@\033[1;32m42lausanne\033[0m: $ "));
}
