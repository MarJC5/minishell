#include "../../inc/minishell.h"

void	ft_exit(t_shell *shell)
{
	free(shell);
	exit(1);
}
