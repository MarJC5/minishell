/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 09:27:18 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/02 12:49:36 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

typedef struct s_export
{
	char	**args;
	char	*name;
	char	*value;
} t_export;


static void	get_all_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		ft_printf("%s\n", env[i++]);
}

void	get_export(int args_count, char *cmd, char *args_value, char **list)
{
	t_export	export;

	if (ft_strcmp("export", cmd) == 0)
	{
		if (args_count == 2)
			get_all_env(list);
		else if (args_count >= 3)
		{
			export.args = ft_split(args_value, '=');
			export.name = export.args[0];
			if (export.args[1] != NULL)
				export.value = export.args[1];
			else
				export.value = "''";
			free(export.args);
			ft_printf("%s=%s", export.name, export.value);
		}
	}
}
