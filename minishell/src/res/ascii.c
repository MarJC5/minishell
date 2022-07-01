/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 19:26:54 by jmartin           #+#    #+#             */
/*   Updated: 2022/05/03 19:27:03 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ascii_prompt(void)
{
	ft_printf("\n\033[1;32m░█▀▄▀█░░▀░░█▀▀▄░░▀░░█▀▀░█░░░░█▀▀░█░░█░\n");
	ft_printf("░█░▀░█░░█▀░█░▒█░░█▀░▀▀▄░█▀▀█░█▀▀░█░░█░\n");
	ft_printf("░▀░░▒▀░▀▀▀░▀░░▀░▀▀▀░▀▀▀░▀░░▀░▀▀▀░▀▀░▀▀\n");
	ft_printf("\033[0;32mby Tpaquier & Jmartin                   \033[0m\n\n");
}

char	*reset_redinput(t_shell *shell, int cmd_index)
{
	shell->cmd[cmd_index]->namei = 0;
	shell->cmd[cmd_index]->namej = 0;
	return (NULL);
}

int	heredoc_while(char *str, int i)
{
	while (str[i])
	{
		if (str[i] && (str[i] == '\"' || str[i] == '\''))
		{
			if (str[i + 1] && str[i + 1] == str[i])
			{
				return (1);
			}
		}
		if (str[i] == ' ')
			i++;
		else if (str[i] == '>')
			return (1);
		else
			return (0);
	}
	return (1);
}

int	heredoc_tester(t_shell *shell, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<')
		{
			if (str[i + 1] && str[i + 1] == '<')
			{
				if (heredoc_while(str, i + 2) == 1)
				{
					str_err("minishell: syntax error near unexpected token `<'",
						NULL);
					shell->err_quote = 1;
					shell->err_pipe = 1;
					free(str);
					return (1);
				}
			}
		}
		i++;
	}
	return (0);
}
