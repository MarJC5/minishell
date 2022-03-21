#include "../../inc/minishell.h"

void	ft_cd(t_shell *shell)
{
	int		i;

	i = 0;
	while (shell->cmd->args[i])
	{
		if (shell->cmd->args[i][0] == 'c' && shell->cmd->args[i][1] == 'd' &&
			 shell->cmd->args[i][2] == '\0')
			break ;
		i++;
	}
	i++;
	if (chdir(shell->cmd->args[i]) == -1)
	{
		ft_printf("cd: ");
		perror(shell->cmd->args[i]);
	}
	else
		chdir(shell->cmd->args[i]);
	ft_printf("%s", getcwd(shell->current_path, 100));
}
