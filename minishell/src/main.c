/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:53:58 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/16 11:42:24 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*init_read(void)
{
	char	*input;
	char	*user;
	char	*prompt;

	user = ft_strjoin(ft_strdup(getenv("USER")), "\033[0m: ");
	prompt = ft_strjoin("\033[1;36mminishell\033[1;37m@\033[1;32m", user);
	input = readline(prompt);
	//init_cmd(shell, input, 1);
	return (input);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	char	*line;

	shell = malloc(sizeof(t_shell));
	set_envp(shell, envp);
	init_signals();
	line = init_read();
	while (line != NULL)
	{
		ft_printf("\033[1;37m>\033[0m %s\n", line);
		line = init_read();
	}
	return (0);
}
