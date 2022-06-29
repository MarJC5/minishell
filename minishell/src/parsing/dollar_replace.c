/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:57:58 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/29 19:31:00 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_replace_empty(char *str, char *dols, int i)
{
	char	*tmp;
	char	*sw;
	char	*ew;
	char	*start;
	char	*ret;

	start = ft_strchr(str, '$');
	i = (int)ft_strlen(str) - (int)ft_strlen(start);
	sw = ft_substr(str, 0, i);
	tmp = ft_strjoin(sw, "");
	i = (int)ft_strlen(str) - (int)ft_strlen(start) + ft_while_for_rien(dols);
	ew = ft_substr(str, i, ft_strlen(str) - i);
	ret = ft_strjoin(tmp, ew);
	ft_free_tab(tmp);
	ft_free_tab(sw);
	ft_free_tab(ew);
	return (ret);
}

static char	*ft_return_dols(char *str)
{
	return (ft_strchr(str, '$'));
}

char	*ft_replace_dols(char *env_value, char *str, int env_size, char *dols)
{
	char	*tmp;
	char	*sw;
	char	*ew;
	char	*ret;
	int		i;

	i = (int)ft_strlen(str) - (int)ft_strlen(ft_return_dols(str));
	sw = ft_substr(str, 0, i);
	tmp = ft_strjoin(sw, env_value);
	i = (int)ft_strlen(str) - (int)ft_strlen(ft_return_dols(str))
		+ env_size + 1;
	ew = ft_substr(str, i, ft_strlen(str) - i);
	ret = ft_strjoin(tmp, ew);
	ft_free_tab(tmp);
	ft_free_tab(sw);
	if (str[i] == '\"' || str[i] == '/' || str[i] == ' '
		|| str[i] == '\0' || str[i] == '$' || str[i] == '\'')
	{
		ft_free_tab(ew);
		return (ret);
	}
	return (ft_replace_empty(str, dols, 0));
}

char	*ft_replace_inter(int status, char *str, char *conv, int i)
{
	char	*tmp;
	char	*sw;
	char	*ew;
	char	*start;
	char	*ret;

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
		ft_free_tab(sw);
		ft_free_tab(ew);
		return (ret);
	}
	return (NULL);
}
