/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:54:56 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/03 09:13:34 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../newlibft/libft.h"
# include <limits.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_cmd
{
	char	*name;
	char	**args;
	int		args_count;
}	t_cmd;

char	*init_cmd(t_cmd	*command, char **argv, int argc);

void	get_pwd(void);
void	set_export(t_cmd *command, char **envp);

#endif
