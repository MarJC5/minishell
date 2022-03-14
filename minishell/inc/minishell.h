/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:54:56 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/14 19:11:24 by jmartin          ###   ########.fr       */
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

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	char	**envp;
	t_cmd	cmd;
}	t_shell;

/**
 * FREE MEM
 */
void	ft_free_tab(char *ptr);
void	ft_free_multi_tab(char **ptr);

/**
 * UTILS
 */
char	*init_cmd(t_shell	*shell, char **args, int start);
char	*append(char before, char *str, char after);

void	set_envp(t_shell *shell, char **envp);

int		args_counter(char **args);

/**
 * PWD
 */
void	pwd(void);

/**
 * ENV
 */
void	env(t_shell *shell);

/**
 * EXPORT
 */
void	export(t_shell *shell);
void	*ft_realloc_env(t_shell *shell, int size, char *value);
int		is_env_valid(char *str);

/**
 * UNSET
 */
void	unset(t_shell *shell);
void	remove_envp(t_shell *shell, char *value, int size);

#endif
