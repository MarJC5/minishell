/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 10:50:02 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/09 10:41:05 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

int	is_env_valid(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = env_name_size(str);
	while (i < j)
	{
		if (ft_isdigit(str[i]) || ft_isalpha(str[i])
			|| str[i] == '_' || str[i] == '=')
			i++;
		else
		{
			str_err("export: not valid in this context: ", str);
			return (0);
		}
	}
	return (j);
}

char	*format_envp(char *value, int size, int is_new)
{
	char	*var;
	char	*arg;
	char	*ret;

	if (ft_strchr(value, ' '))
	{
		arg = ft_substr(value, size + 1, ft_strlen(value));
		var = ft_substr(value, 0, size + 1);
		ret = ft_strjoin(var, append('\"', arg, '\"'));
		free(arg);
		free(var);
	}
	else if (is_new && ft_strchr(value, '=') == NULL)
		ret = ft_strjoin(value, "=\'\'");
	else
		ret = ft_strdup(value);
	return (ret);
}

void	update_envp(t_shell *shell, char *value, int size, int is_valid)
{
	int	i;

	i = -1;
	if (is_valid)
	{
		while (shell->envp[++i])
		{
			if (ft_strncmp(shell->envp[i], value, is_valid) == 0
				&& ft_strchr(value, '=') == NULL)
				break ;
			if (ft_strncmp(shell->envp[i], value, is_valid) == 0
				&& ft_strcmp(shell->envp[i], value) != 0)
			{
				free(shell->envp[i]);
				shell->envp[i] = format_envp(value, is_valid, 0);
				break ;
			}
			else if (ft_strncmp(shell->envp[i], value, is_valid) != 0
				&& i == size - 1)
			{
				add_envp(shell, args_counter(shell->envp) + 1,
					format_envp(value, is_valid, 1));
			}
		}
	}
}

void	set_envp(t_shell *shell, char **envp)
{
	int	i;

	i = -1;
	shell->envp = malloc((args_counter(envp) + 1) * sizeof(char *));
	if (!shell->envp)
		return ;
	while (++i < args_counter(envp))
		shell->envp[i] = format_envp(envp[i], is_env_valid(envp[i]), 0);
	shell->current_path = ft_strdup(getenv("PWD"));
}
