/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:53:58 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/16 13:34:55 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*init_read(t_shell *shell)
{
	char	*input;
	char	*user;
	char	*prompt;

	user = ft_strjoin(getenv("USER"), "\033[0m: ");
	prompt = ft_strjoin("\033[1;36mminishell\033[1;37m@\033[1;32m", user);
	input = readline(prompt);
	free(user);
	free(prompt);
	return (input);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	char	*line;

	shell = malloc(sizeof(t_shell));
	set_envp(shell, envp);
	init_signals();
	line = init_read(shell);
	while (line != NULL)
	{
		ft_printf("\033[1;37m>\033[0m %s\n", line);
		run_cmd(shell, init_cmd(shell, line));
		ft_printf("\n");
		line = init_read(shell);
	}
	return (0);
}
