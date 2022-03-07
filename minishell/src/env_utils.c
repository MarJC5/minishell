/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 10:50:02 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/07 13:24:24 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_env_valid(char *str)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strchr(str, '='))
		j = ft_strlen(str) - ft_strlen(ft_strchr(str, '=')) - 1;
	else
		ft_strlen(str);
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
	return (1);
}

/**
 * @brief Compare all env object
 *
 * @param shell
 */

void	env_comp(t_shell *shell)
{
	int	i;
	int	j;
	int	env_size;
	int	arg_size;

	i = -1;
	if (is_env_valid(shell->cmd->args[0]))
	{
		while (shell->envp[++i])
		{
			/*
				compare before = value
				if no existing -> create new with value or set =''
				if existing -> overwrite the correct env with new value
			*/
		}
	}
}

/**
 * @brief Realloc env array size
 *
 * @param ptr
 * @param size
 * @return void*
 */

void	*ft_realloc_env(char **ptr, int size)
{
	int		i;
	char	**ret;

	i = -1;
	ret = malloc(size + 1);
	if (!ret)
		return (NULL);
	while (++i < (size - 1))
		ft_memcpy(&ret[i], ptr[i], ft_strlen(ptr[i]));
	ret[size + 1] = 0;
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
