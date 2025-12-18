#include "../header.h"

int	execute_external(t_cmd_block *node);

int	execute_pipeline(t_mini *mini)
{
	t_cmd_block	*node;

	node = mini->cmd;
	if (node->next)
		return (execute_multiple(mini->cmd));
	if (is_builtin(node->args))
		return (exec_builtin(node->args, mini));
	return (execute_external(node->args));
}
