/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:54:56 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/03 16:54:27 by jmartin          ###   ########.fr       */
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

typedef struct s_shell
{
	char	**envp;
	t_cmd	*cmd;
}	t_shell;

char	*init_cmd(t_shell	*shell, char **args, int start);

void	set_envp(t_shell *shell, char **envp);
void	get_pwd(void);
void	get_env(t_shell *shell);
void	get_export_env(char **envp);
void	set_export(t_shell *shell);

#endif
