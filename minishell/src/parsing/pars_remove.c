/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 00:18:17 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/30 11:25:46 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*avoid_char(char *str, int i)
{
	char	*src;
	char	*dst;
	int		j;

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

static void	pars_remove_merge(char *merge, int i, char save)
{
	int	count;

	count = 0;
	while (merge[i])
	{
		if ((merge[i] == '\'' || merge[i] == '\"'))
		{
			if (save == '\0')
				save = merge[i];
			if (save == merge[i])
			{
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
}

char	**pars_remove_quote_out(char **str, int i, char save)
{
	char	*tmp;
	char	*merge;

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
		//printf("merge:%s\nstr:%s\n", merge, str[i]);
		tmp = ft_strjoin(merge, str[i++]);
		ft_free_tab(merge);
		merge = ft_strdup(tmp);
		ft_free_tab(tmp);
	}
	pars_remove_merge(merge, 0, save);
	i = (args_counter(str));
	while (i >= 0)
		ft_free_tab(str[i--]);
	free(str);
	str = ft_split(merge, 24);
	return (str);
}
