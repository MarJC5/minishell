/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:13:55 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/15 17:43:46 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pars_cr_realloc(char *args, char *newval, int i, int j)
{
	char	*begin;
	char	*end;
	char	*tmp;

	begin = NULL;
	end = NULL;
	tmp = NULL;
	if (args[i] == '?')
	{
		begin = ft_substr(args, 0, (j - 1));
		end = ft_substr(args, j + 1, ((int)ft_strlen(begin) - j));
		tmp = ft_strjoin(begin, newval);
		ft_printf("end |--> %s\n", end);
		tmp = ft_strjoin(begin, newval);
		args = ft_strjoin(tmp, end);
		ft_printf("result |==> %s\n", args);
		free(begin);
		free(end);
		free(tmp);
	}
	else
		args = newval;
}

void	pars_cr_itao(int ret_val, char *args, int i)
{
	char	*ret;

	ret = ft_itoa(ret_val);
	pars_cr_realloc(args, ret, i, 1);
	free(ret);
}

void	pars_cr_arg(t_shell *shell, char *args, int j)
{
	char	*str;

	if (args[j] == '$')
	{
		if (args[j + 1] == '?')
			pars_cr_itao(g_exit_stat, args, j);
		else if (args[j + 1] != '\0')
		{
			str = get_env_var(shell, args);
			ft_printf("new val|-> %s\n", str);
			if (str)
			{
				pars_cr_realloc(args, ft_strjoin(ft_substr(args, 0, j - 1), str), j, shell->env_size);
				ft_free_tab(str);
			}
		}
	}
}

void	pars_inside_quote(t_shell *shell, char **args, int c)
{
	int	i;
	int j;
	int	qpose;
	int	dpose;

	i = 0;
	while (args[i] != NULL)
	{
		qpose = ft_strchr_pos(args[i], c);
		dpose = ft_strchr_pos(args[i], '$');
		if (dpose >= 0)
		{
			if (qpose >= 0)
			{
				j = qpose;
				while (args[i][j])
				{
					j++;
					if (args[i][j] == c)
						break ;
				}
				if (qpose < dpose && j > dpose)
					;
			}
			else
				pars_cr_arg(shell, args[i], dpose);
		}
		i++;
	}
}