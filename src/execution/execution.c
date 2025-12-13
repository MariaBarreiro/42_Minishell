#include "../header.h"

int	execute_multiple(t_cmd_block **list)
{
	t_cmd_block		*cmd;
	int				n;
	int				(*pipes)[2];
	pid_t			*pids;
	int				i;

	cmd = *list;
	n = count_cmds(cmd);
	pipes = create_pipes(n);
	pids = malloc(sizeof(pid_t) * n);
	i = 0;
	while (cmd)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			child_process(cmd, pipes, i, n);
		cmd = cmd->next;
		i++;
	}
	close_all_pipes(pipes, n);
	wait_all_children(pids, n);
	free(pipes);
	free(pids);
	return (0);
}

int	execute_external(t_cmd_block *node);

int	count_commands(t_cmd_block *cmd)
{
	int	i;

	while (cmd)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}

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
