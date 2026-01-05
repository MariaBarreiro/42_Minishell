#include "../header.h"

int	execute_multiple(t_mini *mini)
{
	t_cmd_block		*cmd;
	int				n;
	int				(*pipes)[2];
	pid_t			*pids;
	int				i;

	cmd = mini->cmd;
	n = count_cmds(cmd);
	pipes = create_pipes(n);
	pids = malloc(sizeof(pid_t) * n);
	i = 0;
	while (cmd)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			child_process(mini, pipes, i, n);
		cmd = cmd->next;
		i++;
	}
	close_all_pipes(pipes, n);
	wait_all_children(pids, n);
	free(pipes);
	free(pids);
	return (0);
}

static void	child_process(t_mini *mini, int (*p)[2], int i, int n)
{
	setup_child_pipes(i, n, p);
	setup_redirections(mini->cmd);
	execute_cmd(mini->cmd, mini->my_env);
}


static void	setup_child_pipes(int i, int total, int (*p)[2])
{
	int	j = 0;

	if (i == 0)
		dup2(p[0][1], 1);
	else if (i == total - 1)
		dup2(p[i - 1][0], 0);
	else
	{
		dup2(p[i - 1][0], 0);
		dup2(p[i][1], 1);
	}
	while (j < total - 1)
	{
		close(p[j][0]);
		close(p[j][1]);
		j++;
	}
}

void	execute_child(t_mini *mini)
{
	t_cmd_block	*cmd;

	cmd = mini->cmd;
	if (is_builtin(cmd->args))
		exit(execute_builtin_child(cmd));
	execve(resolve_path(cmd->args[0]), cmd->args, mini);
	perror("execve");
	exit(1);
}
