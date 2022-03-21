/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:54:56 by jmartin           #+#    #+#             */
/*   Updated: 2022/03/21 09:26:06 by jmartin          ###   ########.fr       */
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
	int		ispipe;
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
void	ft_free_read_args(t_shell *shell, char *line);

/**
 * SHELL
 */
int		run_cmd(t_shell *shell, char *cmd);
void	set_envp(t_shell *shell, char **envp);
char	*init_cmd(t_shell *shell, char *args);
char	*init_read(void);

/**
 * UTILS
 */
void	ascii_prompt(void);
void	str_err(char *str, char *err);
char	*append(char before, char *str, char after);
int		args_counter(char **args);


/**
 * PWD
 */
void	pwd(t_shell *shell);

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
int		env_name_size(char *str);

/**
 * UNSET
 */
void	unset(t_shell *shell);
void	*remove_envp(t_shell *shell, char *value, int size);

/**
 * ECHO
 */
void	ft_echo(t_shell *shell);

/**
 * CD
 */
void	ft_cd(t_shell *shell);

/**
 * SIGNALS
 */
void	init_signals(void);
void	ctrl_c_handler(int sig);

#endif
