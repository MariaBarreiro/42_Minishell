#include "../header.h"

static int	execute_external(t_mini *mini)
{
	setup_redirections(mini->cmd);
	return (execute_cmd(mini->cmd, mini->my_env));
}

int	execute_pipeline(t_mini *mini)
{
	t_cmd_block	*cmd;

	cmd = mini->cmd;
	if (cmd->next)
		return (execute_multiple(mini));
	if (is_builtin(cmd->args))
		return (exec_builtin(cmd->args, mini));
	return (execute_external(mini));
}
