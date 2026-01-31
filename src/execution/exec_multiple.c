#include "../../includes/minishell.h"

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

static void	setup_child_pipes(t_cmd_block *cmd, int i, int total, int (*p)[2])
{
	int	j;

	j = 0;
	if (i > 0)
		dup2(p[i - 1][0], STDIN_FILENO);
	if (i < total - 1 && cmd->outputs == NULL)
		dup2(p[i][1], STDOUT_FILENO);
	while (j < total - 1)
	{
		close(p[j][0]);
		close(p[j][1]);
		j++;
	}
}

static void	child_process(t_mini *mini, t_cmd_block *cmd, int (*p)[2], int i, int n_cmds)
{
	setup_child_pipes(cmd, i, n_cmds, p);
	setup_redirections(cmd);
	if (is_builtin(cmd->args))
		exit(exec_builtin(cmd->args, mini));
	execute_cmd(cmd, mini->my_env);
	exit(1);
}

int	execute_multiple(t_mini *mini)
{
	t_cmd_block		*cmd;
	int				n_cmds;
	int				(*pipes)[2];
	pid_t			*pids;
	int				i;

	cmd = mini->cmd;
	n_cmds = count_cmds(cmd);
	pipes = create_pipes(n_cmds);
	pids = malloc(sizeof(pid_t) * n_cmds);
	i = 0;
	while (cmd)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			child_process(mini, cmd, pipes, i, n_cmds);
		cmd = cmd->next;
		i++;
	}
	close_all_pipes(pipes, n_cmds);
	wait_all_children(pids, n_cmds, mini);
	free(pipes);
	free(pids);
	return (mini->exit_stts);
}
