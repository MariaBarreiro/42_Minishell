#include "../../includes/minishell.h"

int		count_cmds(t_cmd_block *cmd)
{
	int	i;
	t_cmd_block *temp;

	i = 0;
	temp = cmd;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

void	close_all_pipes(int (*pipes)[2], int n)
{
	int	i;

	i = 0;
	while (i < n - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	handle_status(int status, t_mini *mini)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			mini->exit_stts = 130;
		else if (sig == SIGQUIT)
			mini->exit_stts = 131;
		else
			mini->exit_stts = 128 + sig;
	}
	else if (WIFEXITED(status))
		mini->exit_stts = WEXITSTATUS(status);
	else
		mini->exit_stts = 1;
}

void	wait_all_children(pid_t *pids, int n, t_mini *mini)
{
	int	status;
	int	i;

	i = 0;
	while (i < n)
	{
		if (waitpid(pids[i], &status, 0) > 0 && i == n - 1)
			handle_status(status, mini);
		i++;
	}
}

/* void	wait_all_children(pid_t *pids, int n)
{
	int	i;
	int	status;

	i = 0;
	while (i < n)
	{
		waitpid(pids[i], &status, 0);
		if (i == n - 1 && WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		if (i == n - 1 && WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
		i++;
	}
} */