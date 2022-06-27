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
	return (c);
}

/*int ft_count_badquote(t_shell *shell, int cmd_index)
{

}*/

/*char **pars_remove_quote_out(t_shell *shell, int cmd_index, char **str)
{
	char **tmp;
	char **stmp;
	int count;
	int i;
	int g;
	int c;
	int i2;

	i = 0;
	i2 = 0;
	g = 0;
	c = 0;
	tmp = NULL;
	stmp = NULL;
	count = ft_count_badquote(shell, cmd_index);
	tmp = ft_calloc(count, sizeof(char *));
	count = 0;
	shell->sq = '\0';
	shell->eq = '\0';
	shell->sqi = 0;
	shell->sqj = 0;
	while (str[count])
	{
		if (count != shell->sqi && c == 0)
			tmp[i++] = ft_strdup(str[count++]);
		else
		{
			stmp = ft_split_with_delimiter(str[count], shell->sq);
			while (stmp[i2])
			{
				if (stmp[i2][0] != shell->sq)
					tmp[i++] = strdup(stmp[i2++]);
				else
					c++;
				if (c == 2)
					c = 0;
			}
			count++;
			g = (args_counter(stmp));
			while (g >= 0)
				ft_free_tab(stmp[g--]);
			free(stmp);
		}
	}
	int y = 0;
	while (tmp[y])
		printf("-> %s\n", tmp[y++]);
	while (i >= 0)
		ft_free_tab(str[i--]);
	free(str);
	return (tmp);
}*/

/*char **pars_remove_quote_out(t_shell *shell, int cmd_index, char **str)
{
	char **tmp;
	char **stmp;
	int count;
	int i;
	int g;
	int c;
	int i2;

	i = 0;
	i2 = 0;
	g = 0;
	c = 0;
	tmp = NULL;
	stmp = NULL;
	count = ft_count_badquote(shell, cmd_index);
	tmp = ft_calloc(count, sizeof(char *));
	count = 0;
	shell->sq = '\0';
	shell->eq = '\0';
	shell->sqi = 0;
	shell->sqj = 0;
	while (str[count])
	{
		if (str[count] == shell->sqi)
	}
	int y = 0;
	while (tmp[y])
		printf("-> %s\n", tmp[y++]);
	while (i >= 0)
		ft_free_tab(str[i--]);
	free(str);
	return (tmp);
}*/

char    **pars_space(t_shell *shell, int i, int cmd_index)
{
	char **tmp;
	int count;
	int i2;

	int y = 0;
	while (shell->cmd[cmd_index]->args[y])
		printf("-%s-\n", shell->cmd[cmd_index]->args[y++]);

	i2 = 0;
	tmp = NULL;
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
			if (shell->sq != '\0' && shell->eq == '\0')
				count++;
		}
		if (ft_onlyspace(shell->cmd[cmd_index]->args[i]) && count == 0)
			i++;
		else
		{
			quote_finder_two(shell, shell->cmd[cmd_index]->args[i], 1);
			tmp[i2++] = ft_strdup(shell->cmd[cmd_index]->args[i++]);
		}
		if (shell->eq != '\0')
			count = 0;
		printf("count %i\n", count);
	}
	/*int y = 0;
	while (tmp[y])
		printf("%s\n", tmp[y++]);*/
	//tmp = pars_remove_quote_out(shell, cmd_index, tmp);
	while (i >= 0)
		ft_free_tab(shell->cmd[cmd_index]->args[i--]);
	free(shell->cmd[cmd_index]->args);
	return (tmp);
}

void	pars_args(t_shell *shell, char *args, int cmd_index)
{
	char	**tmp;

	tmp = ft_split(args, ' ');
	shell->cmd[cmd_index] = malloc(sizeof(t_cmd));
	shell->cmd[cmd_index]->shell = shell;
	shell->cmd[cmd_index]->in = -1;
	shell->cmd[cmd_index]->out = -1;
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

