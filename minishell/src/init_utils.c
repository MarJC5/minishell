/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:16:18 by jmartin           #+#    #+#             */
/*   Updated: 2022/04/11 07:31:19 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#include "../inc/minishell.h"

/**
 * @brief Save user command to proceed them in the correct order
 *
 * @param shell
 * @param args
 * @param start
 * @return char*
 */

int	isrediorpipe(t_shell *shell, char sign)
{
	int	i;
	int	j;

	i = 0;
	while (shell->cmd->args[i])
	{
		j = 0;
		while (shell->cmd->args[i][j])
		{
			if (shell->cmd->args[i][j] == sign)
			{
				shell->cmd->i = i;
				shell->cmd->j = j;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	is_pipe(char *line, t_shell *shell)
{
	int	i;
	int pipe;
	int redi;

	pipe = 0;
	redi = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '|' && pipe == 0)
			pipe = 1;
		if (line[i] == '>' && pipe == 0)
			redi = 2;
		i++;
	}
	shell->cmd->ispipe = pipe;
	shell->cmd->redi = redi;
}

int	oneword(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i] == ' ')
			return (0);
		i++;
	}
	return (1);
}

char	*init_cmd(t_shell *shell, char *args)
{
	shell->cmd = malloc(sizeof(t_cmd));
	is_pipe(args, shell);
	if (oneword(args) == 1)
	{
		shell->cmd->args = ft_split_with_delimiter(args, '>');
		printf("%s\n", shell->cmd->args[0]);
		printf("%s\n", shell->cmd->args[1]);
		printf("%s\n", shell->cmd->args[2]);
	}
	else
		shell->cmd->args = ft_split(args, ' ');
	shell->cmd->name = shell->cmd->args[0];
	shell->cmd->args_count = args_counter(shell->cmd->args);
	return (shell->cmd->name);
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
