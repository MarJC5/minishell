/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:54:56 by jmartin           #+#    #+#             */
/*   Updated: 2022/06/21 16:57:43 by jmartin          ###   ########.fr       */
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
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

/**
 * GLOBAL
 */
int	g_exit_stat;

/**
 * STRUCT
 */

typedef struct s_cmd
{
	char			**args;
	char			*pwd;
	char			*name;
	char			*pars_args;
	int				start;
	int				namei;
	int				namej;
	int				out;
	int				in;
	pid_t			pid;
	int				cmd_pos;
	int				quotted;
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
	int			heredoc;
	int			env_size;
	int			fd;
	int			cmd_count;
	int			out_status;
	int			in_status;
	int			exit_status;
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
void	exit_status(int wstatus);
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
char	*arg_to_lower(char *str);
int		str_err(char *str, char *err);
int		str_perr(char *name, char *arg);
int		args_counter(char **args);
int		ft_isspace(char *str);
void	old_fd(t_shell *shell, int i);
int		ft_strchr_pos(char *s, char c);

/**
 * PWD
 */
void	pwd(t_shell *shell, int cmd_index);

/**
 * ENV
 */
void	env(t_shell *shell, int cmd_index);
char	*get_env_var(t_shell *shell, char *arg);
char	*env_updater(t_shell *shell, char *name, char *value);

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
void	pars_echo_endl(t_shell *shell, char **args, int cmd_index, int start);

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
void	init_signals(struct termios *saved);
void	ctrl_handler(int sig);

/**
 * PATH
 */
void	path_exec(t_shell *shell, int cmd_index);
void	check_access(t_shell *shell, int cmd_index);
char	**path_finder(t_shell *shell);
int		dir_exist(t_shell *shell, int cmd_index);

/**
 * REDIRECTION & PIPE
 */
void	pipex(t_shell *shell);
void	redirection(t_shell *shell, int cmd_index);
void	is_pipe(char *line, t_shell *shell);
void	close_loop(t_shell *shell);
int		isrediorpipe(t_shell *shell, int cmd_index, char sign);
int		isdoubleredi(char **args, char sign);
char	*getname(t_shell *shell, char **args, int i, int j, int cmd_index);
int		redirection_input(t_shell *shell, int cmd_index);
char	**redirection_arg(t_shell *shell, int cmd_index, int i, int j);
int		ft_more_redi(char **args, char sign);
void	heredoc(t_shell *shell, int cmd_index);

/**
 * QUOTE
 *
 */

int		check_read_quote(char *str);
int		quote_counter(char *s, char c);
char	*remove_char(char *str, char c);
char	*remove_append(char *str, char c);
char	*rm_quote_out(char *str, char c);
void	pars_cmd_name_quote(char *str);
void	pars_args(t_shell *shell, char *args, int cmd_index);
char	*pars_cr_realloc(char *args, char *newval, int i, int j);
char	*pars_cr_arg(t_shell *shell, char *args, int j);
void	pars_inside_quote(t_shell *shell, int cmd_index, int c);
void	pars_remove_quote(t_shell *shell, int cmd_index, int c, int out);
void	pars_first_trim(t_shell *shell, char *args, int cmd_index, int i);

#endif