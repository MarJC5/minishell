/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:16:18 by jmartin           #+#    #+#             */
/*   Updated: 2022/04/11 15:11:12 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	split_args_cmd(t_shell *shell, char *args)
{
	char	**tmp;
	int		i;

	i = -1;
	tmp = ft_split(args, '|');
	while (tmp[++i])
	{
		shell->cmd[i] = malloc(sizeof(t_cmd));
		shell->cmd[i]->cmd_pos = i;
		shell->cmd[i]->args = ft_split(tmp[i], ' ');
		shell->cmd[i]->name = shell->cmd[i]->args[0];
		shell->cmd[i]->args_count = args_counter(shell->cmd[i]->args);
	}
	ft_free_multi_tab(tmp);
}

void	init_cmd(t_shell *shell, char *args)
{
	int	j;

	is_pipe(args, shell);
	if (shell->ispipe >= 1)
		j = shell->ispipe + 1;
	else
		j = 1;
	shell->cmd_count = j;
	shell->cmd = malloc(j * sizeof(t_cmd));
	if (!shell->cmd)
		return ;
	if (j == 1)
	{
		shell->cmd[0] = malloc(sizeof(t_cmd));
		shell->cmd[0]->cmd_pos = 0;
		shell->cmd[0]->args = ft_split(args, ' ');
		shell->cmd[0]->name = shell->cmd[0]->args[0];
		shell->cmd[0]->args_count = args_counter(shell->cmd[0]->args);
	}
	else if (j > 1)
		split_args_cmd(shell, args);
}

char	*init_read(t_shell *shell)
{
	char	*input;
	char	*details;
	char	*prompt;

	if (ft_strcmp(shell->current_path, getenv("HOME")) == 0
		|| ft_strcmp(shell->current_path, "/") == 0 )
		details = ft_strdup("\033[0m:~");
	else
		details = ft_strjoin(getenv("USER"), ft_strjoin("\033[0m:",
					ft_strrchr(shell->current_path, '/') + 1));
	prompt = ft_strjoin("\n\033[1;36mminishell\033[1;37m@\033[1;32m",
			ft_strjoin(details, " $ "));
	input = readline(prompt);
	free(details);
	free(prompt);
	return (input);
}
