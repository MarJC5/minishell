/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartin <jmartin@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:54:56 by jmartin           #+#    #+#             */
/*   Updated: 2022/05/30 16:22:58 by jmartin          ###   ########.fr       */
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
	int				out;
	int				in;
	pid_t			pid;
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
char	*get_env_var(t_shell *shell, char *arg);

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
void	init_signals(struct termios *saved);
void	ctrl_handler(int sig);

/**
 * PATH
 */
void	path_exec(t_shell *shell, int cmd_index);
void	open_dir(t_shell *shell, char **path, char *str, int cmd_index);
char	**path_finder(t_shell *shell);
char	*bin_chek(char **split, char *str);
int		dir_exist(t_shell *shell, char *str);

/**
 * REDIRECTION & PIPE
 */
void	pipex(t_shell *shell);
void	redirection(t_shell *shell, char **args);
void	is_pipe(char *line, t_shell *shell);
void	close_loop(t_shell *shell);
int		isrediorpipe(t_shell *shell, char **args, char sign);
int		isdoubleredi(char **args, char sign);
char	*getname(char **args, int i, int j);

/**
 * QUOTE
 *
 */
int		char_counter(char *s, int c);

#endif
