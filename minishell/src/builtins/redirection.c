#include "../../inc/minishell.h"

char	*getname(t_shell *shell, int i, int j, int g)
{
	char	*name;

	if	(shell->cmd->args[i][j + 1] && shell->cmd->args[i][j + 1] != '>')
		name = malloc(ft_strlen(&shell->cmd->args[i][++j]) + 1);
	else if (shell->cmd->args[i][j + 1] == '>' && shell->cmd->args[i][j + 2])
		name = malloc(ft_strlen(&shell->cmd->args[i][j += 2]) + 1);
	else
	{
		if (shell->cmd->args[i + 1])
		{
			name = malloc(ft_strlen(shell->cmd->args[++i]) + 1);
			j = 0;
		}
		else
			return (NULL);
	}
	while (shell->cmd->args[i][j])
	{
		name[g] = shell->cmd->args[i][j];
		g++;
		j++;
	}
	name[g] = '\0';
	return (name);
}

int	isdoubleredi(t_shell *shell, char sign)
{
	int	i;
	int	j;

	i = 0;
	while (shell->cmd->args[i])
	{
		j = 0;
		while (shell->cmd->args[i][j])
		{
			if (shell->cmd->args[i][j] == sign)
			{
				if (shell->cmd->args[i][j + 1] == sign)
					return (2);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	redirection(t_shell *shell, int fonc)
{
	int		i;
	int		fd;
	char	*name;

	i = -1;
	name = getname(shell, shell->cmd->i, shell->cmd->j, 0);
	if (isdoubleredi(shell, '>') == 2)
		fd = open(name, O_CREAT | O_RDWR | O_APPEND, 0666);
	else
		fd = open(name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fonc == 1 && shell->cmd->echo)
	{
		write(fd, shell->cmd->echo, ft_strlen(shell->cmd->echo));
		free(shell->cmd->echo);
	}
	else if (fonc == 2)
		write(fd, shell->cmd->pwd, ft_strlen(shell->cmd->pwd));
	else if (fonc == 3)
	{
		while (shell->envp[++i])
		{
			write(fd, shell->envp[i], ft_strlen(shell->envp[i]));
			write(fd, "\n", 1);
		}
	}
	else if (fonc == 4)
	{
		while (shell->envp[++i])
		{
			if (ft_strcmp(ft_strchr(shell->envp[i], '='), "=\'\'") != 0)
			{
				write(fd, shell->envp[i], ft_strlen(shell->envp[i]));
				write(fd, "\n", 1);
			}
		}
	}
	close(fd);
	free(name);
}
