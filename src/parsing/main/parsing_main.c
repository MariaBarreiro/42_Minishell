#include "../../../includes/minishell.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

/*
	Read line.
	Create history.
	Handle Ctrl + c.
	Call tokenizer.
	Return exit value.
*/

void	init_minishell(t_mini *mini, char **envp)
{
	mini->cmd = NULL;
	mini->exit_stts = 0;
	if (envp && envp[0])
		mini->my_env = init_env(envp);
	else
	{
		mini->my_env = NULL;
		if (init_minimal_env(&mini->my_env) != 0)
		{
			ft_putstr_fd("minishell: failed to init environment\n", 2);
			exit(1);
		}
	}
}
