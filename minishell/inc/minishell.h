/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:54:56 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/16 14:32:43 by jmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../newlibft/libft.h"
# include <limits.h>
# include <stdio.h>
# include <errno.h>
# include <signal.h>
# include <termios.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

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
 * FREE MEM
 */
void	ft_free_tab(char *ptr);
void	ft_free_multi_tab(char **ptr);

/**
 * SHELL
 */
int		run_cmd(t_shell *shell, char *cmd);
void	set_envp(t_shell *shell, char **envp);
char	*init_cmd(t_shell *shell, char *args);
char	*init_read(t_shell *shell);

/**
 * UTILS
 */
void	str_err(char *str, char *err);
char	*append(char before, char *str, char after);
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
void	update_envp(t_shell *shell, char *value, int size, int is_valid);
void	*add_envp(t_shell *shell, int size, char *value);
char	*format_envp(char *value, int size, int is_new);
int		is_env_valid(char *str);

/**
 * UNSET
 */
void	unset(t_shell *shell);
void	*remove_envp(t_shell *shell, char *value, int size);

/**
 * SIGNALS
 */
void	init_signals(void);
void	ctrl_c_handler(int sig);

#endif
