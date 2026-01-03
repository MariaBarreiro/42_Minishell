#include "../header.h"

int	execute_external(t_mini *mini)
{
	setup_redirections(mini->cmd);
	execute_cmd(mini->cmd, mini->my_env);
}

int	execute_pipeline(t_mini *mini)
{
	t_cmd_block	*node;

	node = mini->cmd;
	if (node->next)
		return (execute_multiple(mini));
	if (is_builtin(node->args))
		return (exec_builtin(node->args, mini));
	return (execute_external(mini));
}
