#include "../../inc/minishell.h"

void	ft_cd(t_shell *shell)
{
	char	*path;
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
	path = ft_strdup("");
	ft_printf("%s\n", getcwd(path, 100));
	free(path);
}
