/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:54:56 by jmartin           #+#    #+#             */
/*   Updated: 2022/04/12 11:56:50 by jmartin          ###   ########.fr       */
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
	char			**args;
	char			*pwd;
	char			*name;
	int				out;
	int				in;
	int				cmd_pos;
	int				args_count;
	struct s_shell	*shell;
	void			(*func)(struct s_shell *, int);
}	t_cmd;

typedef struct s_shell
{
	char		**envp;
	char		*current_path;
	int			ispipe;
	int			bcklash_n;
	int			redi;
	int			i;
	int			j;
	int			fd;
	int			cmd_count;
	t_cmd		**cmd;
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
int		run_cmd(t_shell *shell);
void	set_envp(t_shell *shell, char **envp);
void	init_cmd(t_shell *shell, char *args);
void	init_func(t_shell *shell, int i);
char	*init_read(t_shell *shell);

/**
 * UTILS
 */
void	ascii_prompt(void);
void	builtin_error(t_shell *shell, int cmd_index);
char	*append(char before, char *str, char after);
int		str_err(char *str, char *err);
int		args_counter(char **args);
int		str_cmd_comp(char *cmd, char *comp);
int		ft_isspace(char *str);

/**
 * PWD
 */
void	pwd(t_shell *shell, int cmd_index);

/**
 * ENV
 */
void	env(t_shell *shell, int cmd_index);
void	get_env_var(t_shell *shell, char *arg);

/**
 * EXPORT
 */
void	export(t_shell *shell, int cmd_index);
void	update_envp(t_shell *shell, char *value, int size, int is_valid);
void	*add_envp(t_shell *shell, int size, char *value);
char	*format_envp(char *value, int size, int is_new);
int		is_env_valid(char *str);
int		env_name_size(char *str);

/**
 * UNSET
 */
void	unset(t_shell *shell, int cmd_index);
void	*remove_envp(t_shell *shell, char *value, int size);

/**
 * ECHO
 */
void	ft_echo(t_shell *shell, int cmd_index);

/**
 * CD
 */
void	ft_cd(t_shell *shell, int cmd_index);

/**
 * EXIT
 */
void	ft_exit(t_shell *shell, int cmd_index);

/**
 * SIGNALS
 */
void	init_signals(void);
void	ctrl_c_handler(int sig);

/**
 * REDIRECTION & PIPE
 */
void	pipex(t_shell *shell);
void	redirection(t_shell *shell, char **args);
void	is_pipe(char *line, t_shell *shell);
int		isrediorpipe(t_shell *shell, char **args, char sign);
int		isdoubleredi(char **args, char sign);
char	*getname(char **args, int i, int j);

#endif
