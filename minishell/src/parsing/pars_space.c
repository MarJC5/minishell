/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 00:11:56 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/28 15:31:45 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_strchr_env(char *str, char c)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	ret = malloc(sizeof(char) * i + 1);
	if (!ret)
		return (NULL);
	j = 0;
	while (j < i)
	{
		ret[j] = str[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

static char	*ft_strchr_no_delimiter(const char *s, int c)
{
	int	i;

	i = 0;
	if (c == '\0')
	{
		s += ft_strlen(s);
		return ((char *)s);
	}
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *)&s[i] + 1);
		i++;
	}
	return (NULL);
}

char	*ret_err(char *ew)
{
	char	*err1;
	char	*tmp;

	tmp = NULL;
	err1 = NULL;
	printf("ERROR 42\n");
	err1 = ft_strchr_no_delimiter(ew, '\"');
	if (err1)
	{
		if (ft_isalnum(err1[0]) == 1 || err1[0] == '\"')
		{
			tmp = ft_strdup(ft_strchr(ew, '\"'));
			ft_free_tab(ew);
			return (tmp);
		}
	}
	ft_free_tab(ew);
	return (NULL);
}

char	*ft_replace_dols(char *env_value, char *str, int env_size)
{
	char	*tmp;
	char	*sw;
	char	*ew;
	char	*start;
	char	*ret;
	int		i;

	start = ft_strchr(str, '$');
	i = (int)ft_strlen(str) - (int)ft_strlen(start);
	sw = ft_substr(str, 0, i);
	tmp = ft_strjoin(sw, env_value);
	i = (int)ft_strlen(str) - (int)ft_strlen(start) + env_size + 1;
	ew = ft_substr(str, i, ft_strlen(str) - i);
	ret = ft_strjoin(tmp, ew);
	free(tmp);
	free(sw);
	printf("IN ERROR 1 - %c\n", str[i]);
	if (str[i] == '\"' || str[i] == '/' || str[i] == ' ' || str[i] == '\0' || str[i] == '$')
	{
		printf("IN ERROR 2\n");
		ft_free_tab(ew);
		return (ret);
	}
	return (ret_err(ew));
}

char	*ft_replace_inter(int status, char *str, char *conv)
{
	char	*tmp;
	char	*sw;
	char	*ew;
	char	*start;
	char	*ret;
	int		i;
	
	conv = ft_itoa(status);
	if (ft_strchr(str, '$') != NULL)
	{
		start = ft_strchr(str, '$');
		i = (int)ft_strlen(str) - (int)ft_strlen(start);
		sw = ft_substr(str, 0, i);
		tmp = ft_strjoin(sw, conv);
		i = (int)ft_strlen(str) - (int)ft_strlen(start) + 2;
		ew = ft_substr(str, i, ft_strlen(str) - i);
		ret = ft_strjoin(tmp, ew);
		ft_free_tab(tmp);
		free(sw);
		free(ew);
		return (ret);
	}
	return (NULL);
}

void	pars_dollars(t_shell *shell, int cmd_index, int i, char *tmp)
{
	int		j;
	char	*dols;
	char	*env_name;
	size_t	env_size;

	j = 0;
	dols = ft_strchr_no_delimiter(shell->cmd[cmd_index]->args[i], '$');
	if (dols == NULL)
		return ;
	while (shell->envp[j])
	{
		env_name = ft_strchr_env(shell->envp[j], '=');
		env_size = ft_strlen(env_name);
		if (dols[0] == '?')
		{
			tmp = ft_replace_inter(g_exit_stat, shell->cmd[cmd_index]->args[i], NULL);
			if (tmp != NULL)
			{
				ft_free_tab(shell->cmd[cmd_index]->args[i]);
				shell->cmd[cmd_index]->args[i] = tmp;
			}
		}
		if (ft_strncmp(dols, env_name, env_size) == 0)
		{
			printf("IN ERROR\n");
			tmp = ft_replace_dols(ft_strchr(shell->envp[j], '=') + 1,
					shell->cmd[cmd_index]->args[i], env_size);
			if (tmp != NULL)
			{
				ft_free_tab(shell->cmd[cmd_index]->args[i]);
				shell->cmd[cmd_index]->args[i] = tmp;
			}
		}
		j++;
		free(env_name);
	}
	dols = ft_strchr_no_delimiter(shell->cmd[cmd_index]->args[i], '$');
	if (dols && tmp != NULL)
		pars_dollars(shell, cmd_index, i, NULL);
}

static void	pars_sp_loop_sq(t_shell *shell, int cmd_index, int *i, int *count)
{
	if (shell->sq == '\0')
		quote_finder(shell, cmd_index, *i);
	else if (shell->sq != '\0')
	{
		quote_finder_two(shell, shell->cmd[cmd_index]->args[*i], 1);
		if (shell->sq != '\0' && shell->eq != '\0')
		{
			*count = 0;
			ft_reset_eq_sq(shell);
		}
		if (shell->sq != '\0' && shell->eq == '\0')
			*count += 1;
	}
}

static void	pars_space_free(t_shell *shell, int cmd_index, int i)
{
	while (i >= 0)
		ft_free_tab(shell->cmd[cmd_index]->args[i--]);
	free(shell->cmd[cmd_index]->args);
}

char	**pars_space(t_shell *shell, int i, int i2, int cmd_index)
{
	char	**tmp;
	int		count;

	count = 0;
	tmp = ft_calloc(ft_counter_space(shell,
				shell->cmd[cmd_index]->args, cmd_index), sizeof(char *));
	ft_reset_eq_sq(shell);
	while (i < args_counter(shell->cmd[cmd_index]->args) - 1)
	{
		pars_sp_loop_sq(shell, cmd_index, &i, &count);
		if (shell->sq != '\'')
			pars_dollars(shell, cmd_index, i, NULL);
		if (ft_onlyspace(shell->cmd[cmd_index]->args[i]) && count == 0)
			i++;
		else
		{
			if (shell->sq == '\0')
				tmp[i2++] = ft_strdup(shell->cmd[cmd_index]->args[i++]);
			else
				tmp[i2++] = ft_join_quote(shell, cmd_index, &i);
			if (i != args_counter(shell->cmd[cmd_index]->args) - 1)
				quote_finder_two(shell, shell->cmd[cmd_index]->args[i], 0);
		}
	}
	pars_space_free(shell, cmd_index, 0);
	return (pars_remove_quote_out(tmp, 0, '\0'));
}
