/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:54:56 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/14 11:59:50 by jmartin          ###   ########.fr       */
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


/**
 * UTILS
 */
char	*init_cmd(t_shell	*shell, char **args, int start);

int		args_counter(char **args);

void	*ft_free_multi_tab(char **ptr);

/**
 * PWD
 */
void	get_pwd(void);

/**
 * ENV
 */
void	update_envp(t_shell *shell, char *value, int size);
void	set_export(t_shell *shell);
void	set_envp(t_shell *shell, char **envp);
void	get_env(t_shell *shell);
void	get_export_env(char **envp);
void	*ft_realloc_env(char **ptr, int size);

int		is_env_valid(char *str);

#endif
