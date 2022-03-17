/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 21:16:18 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/16 14:03:30 by jmartin          ###   ########.fr       */
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

char	*init_cmd(t_shell *shell, char *args)
{
	shell->cmd = malloc(sizeof(t_cmd));
	shell->cmd->args = ft_split(args, ' ');
	shell->cmd->name = shell->cmd->args[0];
	shell->cmd->args_count = args_counter(shell->cmd->args);
	return (shell->cmd->name);
}

char	*init_read(t_shell *shell)
{
	char	*input;
	char	*user;
	char	*prompt;

	user = ft_strjoin(getenv("USER"), "\033[0m: ");
	prompt = ft_strjoin("\033[1;36mminishell\033[1;37m@\033[1;32m", user);
	//input = readline(prompt);
	free(user);
	free(prompt);
	return (input);
}
