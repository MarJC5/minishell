/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 10:50:02 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/14 19:11:06 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_env_valid(char *str)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strchr(str, '='))
		j = ft_strlen(str) - ft_strlen(ft_strchr(str, '='));
	else
		j = ft_strlen(str);
	while (i < j)
	{
		if (ft_isdigit(str[i]) || ft_isalpha(str[i])
			|| str[i] == '_' || str[i] == '=')
			i++;
		else
		{
			printf("export: not valid in this context: %s", str);
			return (0);
		}
	}
	return (j);
}

/**
 * @brief Realloc env array size
 *
 * @param ptr
 * @param size
 * @return void*
 */

void	*ft_realloc_env(t_shell *shell, int size, char *value)
{
	int		i;
	char	**ret;

	i = -1;
	ret = malloc((size + 1) * sizeof(char *));
	if (!ret)
		return (NULL);
	while (++i < (size - 1))
		ret[i] = ft_strdup(shell->envp[i]);
	ret[size - 1] = value;
	ft_free_multi_tab(shell->envp);
	shell->envp = ret;
	return (ret);
}

/**
 * @brief Set the envp object
 *
 * @param shell
 * @param envp
 */

void	set_envp(t_shell *shell, char **envp)
{
	int	i;

	i = -1;
	if (!shell->envp)
	{
		shell->envp = malloc((args_counter(envp) + 1) * sizeof(char *));
		while (++i < args_counter(envp))
			shell->envp[i] = ft_strdup(envp[i]);
	}
}
