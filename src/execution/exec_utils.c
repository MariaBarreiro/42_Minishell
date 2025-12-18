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

void	close_all_pipes(int	*pipes, int n)
{
	
}

void	wait_all_children(pid_t *pids, int n)
{
	int	i;

	i = 0;
	while (i < n)
		waitpid(pids[i++], NULL, 0);
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