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
	int				heredoc;
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
	char		*line;
	char		*redinput;
	int			ispipe;
	int			bcklash_n;
	int			redi;
	int			i;
	int			j;
	int			redinput_err;
	int			env_size;
	int			fd;
	int			fd_in;
	int			cmd_count;
	char		sq;
	char		eq;
	int			sqi;
	int			sqj;
	char		*env_name;
	size_t		ct_dols;
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
char	*init_read(t_shell *shell);
void	exit_status(int wstatus);
void	set_envp(t_shell *shell, char **envp);
void	init_cmd(t_shell *shell, char *args);
void	init_func(t_shell *shell, int i);
int		run_cmd(t_shell *shell);

/**
 * UTILS
 */
char	*append(char before, char *str, char after);
char	*append_last(char *str, char after);
char	*arg_to_lower(char *str);
void	ascii_prompt(void);
void	builtin_error(t_shell *shell, int cmd_index);
int		str_err(char *str, char *err);
int		str_perr(char *name, char *arg);
int		args_counter(char **args);
int		ft_isspace(char *str);

void	old_fd(t_shell *shell);
void	old_fd_two(t_shell *shell);
void	ft_redo_char(t_shell *shell, int cmd_index);
int		ft_onlyspace(char *str);
int		ft_strchr_pos(char *s, char c);
int		path_exist(char **env, char *str);

/**
 * PWD
 */
void	pwd(t_shell *shell, int cmd_index);

/**
 * ENV
 */
char	*get_env_var(t_shell *shell, char *arg);
char	*env_updater(t_shell *shell, char *name, char *value);
void	env(t_shell *shell, int cmd_index);

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
char	**path_finder(t_shell *shell);
void	path_exec(t_shell *shell, int cmd_index);
void	check_access(t_shell *shell, int cmd_index);
int		dir_exist(t_shell *shell, int cmd_index, char *tmp, char *acctmp);

/**
 * REDIRECTION & PIPE
 */
char	*getname(t_shell *shell, int i, int j, int cmd_index);
char	**redirection_arg(t_shell *shell, int cmd_index, int i, int j);
void	pipex(t_shell *shell);
void	redirection(t_shell *shell, int cmd_index);
void	is_pipe(char *line, t_shell *shell);
void	close_loop(t_shell *shell);
void	heredoc(t_shell *shell, int cmd_index);
void	ft_cmd_name_changer(t_shell *shell, int cmd_index);
int		isrediorpipe(t_shell *shell, int cmd_index, char sign);
int		isdoubleredi(char **args, char sign);
int		redirection_input(t_shell *shell, int cmd_index);
int		ft_more_redi(char **args, char sign);

/**
 * QUOTE
 *
 */
char	*remove_char(char *str, char c);
char	*pars_cr_realloc(char *args, char *newval, int i, int j);
char	*pars_cr_arg(t_shell *shell, char *args, int j);
char	*ft_join_quote(t_shell *shell, int cmd_index, int *i);
char	**pars_space(t_shell *shell, int i, int i2, int cmd_index);
char	**pars_remove_quote_out(char **str, int i, char save);
char	quote_counter_sign(char **args, int i, int j, int c);
void	quote_finder_two(t_shell *shell, char *args, int task);
void	ft_reset_eq_sq(t_shell *shell);
void	pars_cmd_name_quote(char *str);
void	pars_args(t_shell *shell, char *args, int cmd_index);
void	quote_finder(t_shell *shell, int cmd_index, int i);
void	replace_spec_char(char *args, int i, int count, char save);
int		quote_counter(char *s, char c);
int		ft_counter_space(t_shell *shell, char **args, int cmd_index);

void	pars_dollars(t_shell *shell, int cmd_index, int i, char *tmp);
char	*ft_strchr_env(char *str, char c);
char	*ft_replace_empty(char *str, char *dols, int i);
char	*ft_replace_dols(char *env_value, char *str, int env_size, char *dols);
char	*ft_replace_inter(int status, char *str, char *conv, int i);
char	*ft_strchr_no_delimiter(const char *s, int c);
int		ft_while_for_rien(char *str);

#endif
