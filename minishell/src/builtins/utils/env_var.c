/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:52:16 by jmartin           #+#    #+#             */
/*   Updated: 2022/04/12 12:21:35 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static int	ft_strchr_pos(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return (i);
		i++;
	}
	return (0);
}

void	get_env_var(t_shell *shell, char *arg)
{
	int		i;
	int		var_len;
	char	*var;

	i = -1;
	while (shell->envp[++i])
	{
		var_len = ft_strchr_pos(shell->envp[i], '=');
		var = ft_substr(shell->envp[i], 0, var_len);
		if (arg[0] == '$' && ft_strcmp(var, ft_strtrim(arg, "$")) == 0)
		{
			ft_putstr_fd(ft_strtrim(shell->envp[i] + var_len, "="), 1);
			free(var);
			break ;
		}
		free(var);
	}
}
