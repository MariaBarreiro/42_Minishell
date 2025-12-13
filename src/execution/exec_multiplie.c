#include "../header.h"

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

int	(*create_pipes(int n))[2]
{
	int	(*p)[2];
	int	i;

	p = malloc(sizeof(int [2]) * (n - 1));
	i = 0;
	while (i < n - 1)
	{
		if (pipe(p[i]) == -1)
			exit(1);
		i++;
	}
	return (p);
}

void	child_process(t_cmd_block *cmd, int (*p)[2], int i, int n)
{
	setup_child_pipes(i, n, p);
	setup_redirections(cmd);
	execute_cmd(cmd);
}

void	setup_child_pipes(int i, int total, int (*p)[2])
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

void	wait_all_children(pid_t *pids, int n)
{
	int	i = 0;

	while (i < n)
		waitpid(pids[i++], NULL, 0);
}

