#include "../header.h"

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

void	wait_all_children(pid_t *pids, int n)
{
	int	i;
	int	status;

	i = 0;
	while (i < n)
	{
		waitpid(pids[i], &status, WNOHANG);
		i++;
	}
}
void	wait_all_children(pid_t *pids, int n)
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
}