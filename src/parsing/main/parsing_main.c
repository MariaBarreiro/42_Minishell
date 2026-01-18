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
	mini->my_env = init_env(envp);
	mini->exit_stts = 0;
}
