/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:16:18 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/30 09:00:33 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Save user command to proceed them in the correct order
 *
 * @param shell
 * @param args
 * @param start
 * @return char*
 */

void	is_pipe(char *line, t_shell *shell)
{
	int	i;
	int pipe;

	pipe = 0;
	i = 0;
	ft_printf("%s\n", line);
	while (line[i])
	{
		if (line[i] == '|')
			pipe = 1;
		i++;
	}
	shell->cmd->ispipe = pipe;
}

char	*init_cmd(t_shell *shell, char *args)
{
	shell->cmd = malloc(sizeof(t_cmd));
	is_pipe(args, shell);
	shell->cmd->args = ft_split(args, ' ');
	shell->cmd->name = shell->cmd->args[0];
	shell->cmd->args_count = args_counter(shell->cmd->args);
	return (shell->cmd->name);
}

char	*init_read(t_shell *shell)
{
	char *input;
	char *details;
	char *prompt;

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
