#include "../../inc/minishell.h"

static int	isp(char **str, int i, int ret)
{
	int	j;

	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '|' || str[i][j] == '>')
			{
				if (ret == 1)
					return (j);
				if (ret == 0)
					return (i);
			}
			j++;
		}
		i++;
	}
	return (0);
}

char	*echo_struct(t_shell *shell, int j, int i)
{
	char	*echo;
	int		g;
	int		c;

	echo = malloc(j + 2);
	g = 0;
	c = 0;
	while (g < j)
	{
		if (shell->cmd->args[i][c])
			echo[g] = shell->cmd->args[i][c];
		else
		{
			i++;
			c = -1;
			echo[g] = ' ';
		}
		g++;
		c++;
	}
	if (shell->cmd->bcklashN == 1)
		echo[g] = '\n';
	echo[g + 1] = '\0';
	return (echo);
}

void	ft_pipe(t_shell *shell, int i)
{
	int	j;
	int	pi;
	int	g;

	g = i;
	j = 0;
	pi = isp(shell->cmd->args, i, 0);
	while (shell->cmd->args[i])
	{
		if (i == pi)
		{
			j += isp(shell->cmd->args, i, 1);
			break ;
		}
		else
			j += (ft_strlen(shell->cmd->args[i]) + 1);
		i++;
	}
	shell->cmd->echo = echo_struct(shell, j, g);
	if (isrediorpipe(shell, '>') == 1)
		redirection(shell, 1);
	/*
	/ start = premier arguments après echo
	/ count = nombre d'argument entre la premiere lettre de i et le pipe
	*/
}

void	ft_wbn(t_shell *shell, int i)
{
	shell->cmd->bcklashN = 1;
	if (isp(shell->cmd->args, i, 0) == 0)
	{
		while (shell->cmd->args[i])
		{
			ft_printf("%s", shell->cmd->args[i++]);
			if (shell->cmd->args[i])
				ft_printf(" ");
		}
		ft_printf("\n");
	}
	else
		ft_pipe(shell, i);
}

void	ft_nbn(t_shell *shell, int i)
{
	if (isp(shell->cmd->args, i, 0) == 0)
	{
		while (shell->cmd->args[i])
		{
			ft_printf("%s", shell->cmd->args[i++]);
			if (shell->cmd->args[i] != NULL)
				ft_printf(" ");
		}
	}
	else
		ft_pipe(shell, i);
}

void	ft_echo(t_shell *shell)
{
	shell->cmd->bcklashN = 0;
	if (shell->cmd->args[1])
	{
		if (shell->cmd->args[1][0] == '-' && shell->cmd->args[1][1] == 'n')
			ft_nbn(shell, 2);
		else
			ft_wbn(shell, 1);
	}
	else
		ft_printf("\n");
}
