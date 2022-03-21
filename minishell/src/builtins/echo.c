#include "../../inc/minishell.h"

static int	isp(char **str, int i, int ret)
{
	int	j;

	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '|')
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

void	ft_pipe(t_shell *shell, int i)
{
	int	j;
	int	pi;
	int	bi;

	j = 0;
	bi = i;
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
// valeur de stockage pour la struct -> 'bi' pour
//à partir de qu'elle argument printf
// et 'i' pour à qu'elle argument stoper et
//'j' pour qu'elle lettre de l'argument 'i'
// - 1 ("test|" = 4), pour s'arreter quand le pipe est là.
}

void	ft_wbn(t_shell *shell, int i)
{
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
	int		i;
	char	*echo;

	i = 1;
	echo = "echo";
	while (shell->cmd->args[i])
	{
		ft_printf("%s\n", shell->cmd->args[i]);
		i++;
	}
	i = 0;
	while (shell->cmd->args[i])
	{
		if (shell->cmd->args[i][0] == echo[0] && shell->cmd->args[i][1] ==
			echo[1] && shell->cmd->args[i][2] == echo[2] && shell->cmd->
			args[i][3] == echo[3] && shell->cmd->args[i][4] == echo[4])
			break ;
		i++;
	}
	if (shell->cmd->args[i + 1])
	{
		if (shell->cmd->args[i + 1][0] == '-' && shell->cmd->args[i + 1][1] == 'n')
			ft_nbn(shell, i + 2);
		else
			ft_wbn(shell, i + 1);
	}
	else
		ft_printf("\n");
	ft_printf("%d\n", shell->cmd->ispipe);
}
