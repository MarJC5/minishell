/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 10:52:16 by jmartin           #+#    #+#             */
/*   Updated: 2022/05/03 12:36:58 by jmartin          ###   ########.fr       */
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

char	*get_env_var(t_shell *shell, char *arg)
{
	int		i;
	int		var_len;
	char	*var;
	char	*str;

	i = -1;
	str = NULL;
	while (shell->envp[++i])
	{
		var_len = ft_strchr_pos(shell->envp[i], '=');
		var = ft_substr(shell->envp[i], 0, var_len);
		if (ft_strcmp(var, ft_strrchr(arg, '$') + 1) == 0)
		{
			str = ft_strtrim(shell->envp[i] + var_len, "=");
			free(var);
			break ;
		}
		free(var);
	}
	return (str);
}
