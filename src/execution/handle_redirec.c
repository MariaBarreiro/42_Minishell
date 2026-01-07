/* #include "../header.h"

void	handle_pipes(int pipes[][2], int i, int total)
{
	int	j;

	if (i == 0)
		dup2(pipes[0][1], STDOUT_FILENO);
	else if (i == total - 1)
		dup2 (pipes[i - 1][0], STDIN_FILENO);
	else
	{
		dup2 (pipes[i - 1][0], STDIN_FILENO);
		dup2 (pipes[i][1], STDOUT_FILENO);
	}
	j = 0;
	while (j < total - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

void	handle_redirs(t_cmd_block *cmd)
{
	int	fd;
	int	i;

	i = 0;
	while (cmd->input && cmd->input[i])
	{
		fd = open(cmd->input[i], O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
		i++;
	}
	i = 0;
	while (cmd->output && cmd->output[i])
	{
		if (cmd->redir_append)
			fd = open(cmd->output[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cmd->output[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		i++;
	}
}
 */