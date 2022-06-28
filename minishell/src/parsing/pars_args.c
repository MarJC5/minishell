/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 08:46:53 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/16 12:52:52 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pars_cmd_name_quote(char *str)
{
	if (quote_counter(str, '\"') == 0)
		remove_char(str, '\"');
	if (quote_counter(str, '\'') == 0)
		remove_char(str, '\'');
}

char quote_counter_sign(char **args)
{
	int	i;
	int	j;
	int c;
	char sign;

	i = 0;
	c = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '\"' || args[i][j] == '\'')
			{
				if (c == 0)
					sign = args[i][j];
				if (sign == args[i][j] && c > 0)
					c = 0;
				else
					c++;
			}
			j++;
		}
		i++;
	}
	if (c != 0)
		return (sign);
	return ('\0');
}

void quote_finder(t_shell *shell, int cmd_index, int i)
{
	int j;

	j = 0;
	while (shell->cmd[cmd_index]->args[i][j])
	{
		if (shell->cmd[cmd_index]->args[i][j] == '\"' || shell->cmd[cmd_index]->args[i][j] == '\'')
		{
			shell->sq = shell->cmd[cmd_index]->args[i][j];
			shell->sqj = i;
			return;
		}
		j++;
	}
	shell->sq = '\0';
}

void quote_finder_two(t_shell *shell, char *args, int task)
{
	int	i;

	i = 0;
	if (task == 0)
	{
		while (args[i])
		{
			if (args[i] == shell->sq)
			{
				shell->eq = args[i];
				return;
			}
			i++;
		}
	}
	else
	{
		i = shell->sqj + 1;
		while (args[i])
		{
			if (args[i] == shell->sq)
			{
				shell->eq = args[i];
				return;
			}
			i++;
		}
	}
}

int ft_counter_space(t_shell *shell, char **args, int cmd_index)
{
	int i;
	int c;
	int i2;
	int count;

	i = 0;
	c = 0;
	count = 0;
	i2 = 0;
	shell->sq = '\0';
	shell->eq = '\0';
	shell->sqi = 0;
	shell->sqj = 0;
	while (args[i])
	{
		if (shell->sq == '\0')
		{
			quote_finder(shell, cmd_index, i);
			shell->sqi = i;
		}
		if (shell->sq != '\0')
			count++;
		if (args[i][0] == ' ' && count == 0)
			;
		else
			c++;
		if (shell->sq != '\0')
		{
			if (shell->sqi == i)
				quote_finder_two(shell, args[i], 1);
			else
				quote_finder_two(shell, args[i], 0);
			if (shell->eq == shell->sq)
			{
				count = 0;
				shell->sq = '\0';
			}
		}
		i++;
		i2++;
	}
	shell->sq = '\0';
	shell->eq = '\0';
	shell->sqi = 0;
	shell->sqj = 0;
	return (++c);
}

char	*avoid_char(char *str, int i)
{
	char	*src;
	char	*dst;
	int     j;

	dst = str;
	src = dst;
	j = 0;
	while (*src != '\0')
	{
		*dst = *src;
		if (i != j++)
			dst++;
		src++;
	}
	*dst = '\0';
	return (dst);
}

char **pars_remove_quote_out(t_shell *shell, int cmd_index, char **str)
{
	char *tmp;
	char *merge;
	char  save;
	int i;
	(void)shell;
	(void)cmd_index;

	i = 0;
	while (i < args_counter(str))
	{
		if (ft_onlyspace(str[i]) == 0)
			append_last(str[i], 24);
		i++;
	}
	i = 0;
	merge = ft_strdup("");
	while (i < args_counter(str))
	{
		tmp = ft_strjoin(merge, str[i++]);
		free(merge);
		merge = ft_strdup(tmp);
		free(tmp);
		printf("->%s<-\n", merge);
	}
	i = 0;
	save = '\0';
	int count = 0;
	while (merge[i])
	{
		if ((merge[i] == '\'' || merge[i] == '\"'))
		{
			if (save == '\0')
				save = merge[i];
			if (save == merge[i])
			{
				printf("count -> %d\n", count);
				count++;
				avoid_char(merge, i);
				i--;
				if (count >= 2)
				{
					save = '\0';
					count = 0;
				}
			}
		}
		i++;
	}
	printf("new str = %s\n", merge);
	i = (args_counter(str));
	while (i >= 0)
		ft_free_tab(str[i--]);
	free(str);
	str = ft_split(merge, 24);
	int y = 0;
	while (str[y])
		printf("[%s]\n", str[y++]);
	return (str);
}

void    ft_redo_char(t_shell *shell, int cmd_index)
{
	int i;
	int j;

	i = 0;
	while (i < args_counter(shell->cmd[cmd_index]->args))
	{
		j = 0;
		while (shell->cmd[cmd_index]->args[i][j])
		{
			if (shell->cmd[cmd_index]->args[i][j] == 27)
				shell->cmd[cmd_index]->args[i][j] = '|';
			else if (shell->cmd[cmd_index]->args[i][j] == 6)
				shell->cmd[cmd_index]->args[i][j] = '<';
			else if (shell->cmd[cmd_index]->args[i][j] == 11)
				shell->cmd[cmd_index]->args[i][j] = '>';
			j++;
		}
		i++;
	}
}

char    *ft_join_quote(t_shell *shell, int cmd_index, int *i)
{
		char    *tmp;
		char    *merge;
		int     c;

		c = 0;
		tmp = ft_strdup("");
		while (*i < args_counter(shell->cmd[cmd_index]->args) - 1 && c == 0)
		{
			quote_finder_two(shell, shell->cmd[cmd_index]->args[*i], 1);
			if (shell->eq != '\0')
				c = 1;
			merge = ft_strjoin(tmp, shell->cmd[cmd_index]->args[*i]);
			printf("merge = %s\n", merge);
			free(tmp);
			tmp = ft_strdup(merge);
			free(merge);
			*i += 1;
		}
		//ft_replace_char(shell, tmp, shell->eq);
		printf("------------------\n");
		return (tmp);
}

char    **pars_space(t_shell *shell, int i, int cmd_index)
{
	char **tmp;
	char *merge;
	int count;
	int i2;

	int y = 0;
	while (shell->cmd[cmd_index]->args[y])
		printf("-%s-\n", shell->cmd[cmd_index]->args[y++]);
	i2 = 0;
	tmp = NULL;
	merge = ft_strdup("");
	count = ft_counter_space(shell, shell->cmd[cmd_index]->args, cmd_index);
	printf("counter : %d\n", count);
	tmp = ft_calloc(count, sizeof(char *));
	count = 0;
	i = 0;
	shell->sq = '\0';
	shell->eq = '\0';
	while (i < args_counter(shell->cmd[cmd_index]->args) - 1)
	{
		if (shell->sq == '\0')
			quote_finder(shell, cmd_index, i);
		else if (shell->sq != '\0')
		{
			quote_finder_two(shell, shell->cmd[cmd_index]->args[i], 1);
			if (shell->sq != '\0' && shell->eq != '\0')
			{
				count = 0;
				shell->sq = '\0';
				shell->eq = '\0';
			}
			if (shell->sq != '\0' && shell->eq == '\0')
				count++;
		}
		if (ft_onlyspace(shell->cmd[cmd_index]->args[i]) && count == 0)
			i++;
		else
		{

			if (shell->sq == '\0')
				tmp[i2++] = ft_strdup(shell->cmd[cmd_index]->args[i++]);
			else
				tmp[i2++] = ft_join_quote(shell, cmd_index, &i);
			if (i != args_counter(shell->cmd[cmd_index]->args) -1)
				quote_finder_two(shell, shell->cmd[cmd_index]->args[i], 0);
		}
	}
	y = 0;
	while (tmp[y])
		printf("|%s|\n", tmp[y++]);
	while (i >= 0)
		ft_free_tab(shell->cmd[cmd_index]->args[i--]);
	free(shell->cmd[cmd_index]->args);
	return (pars_remove_quote_out(shell, cmd_index, tmp));
}

void	pars_args(t_shell *shell, char *args, int cmd_index)
{
	char	**tmp;

	tmp = ft_split(args, ' ');
	shell->cmd[cmd_index] = malloc(sizeof(t_cmd));
	shell->cmd[cmd_index]->shell = shell;
	shell->cmd[cmd_index]->in = -1;
	shell->cmd[cmd_index]->out = -1;
	shell->cmd[cmd_index]->heredoc = 0;
	shell->cmd[cmd_index]->pid = -1;
	shell->cmd[cmd_index]->cmd_pos = cmd_index;
	shell->cmd[cmd_index]->quotted = 0;
	shell->cmd[cmd_index]->name = ft_strdup(tmp[0]);
	pars_cmd_name_quote(shell->cmd[cmd_index]->name);
	if (ft_strchr(args, '\'')  || ft_strchr(args, '\"'))
	{
		shell->cmd[cmd_index]->args = ft_split_with_delimiter(args, ' ');
		if (quote_counter_sign(shell->cmd[cmd_index]->args) == '\0')
			shell->cmd[cmd_index]->args = pars_space(shell, 0, cmd_index);
		else
			str_err("minishell: Erreur missing quote\n", &shell->sq);
	}
	else
		shell->cmd[cmd_index]->args = ft_split(args, ' ');
	shell->cmd[cmd_index]->args_count = args_counter(
			shell->cmd[cmd_index]->args);
	shell->cmd_count++;
	ft_free_multi_tab(tmp);
}
