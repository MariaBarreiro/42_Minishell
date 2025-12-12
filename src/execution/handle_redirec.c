#include "../header.h"

void handle_pipes(t_command_block *cmd, int pipes[][2], int i, int total)
{
	if (i == 0)
		dup2(pipes[0][1], STDOUT_FILENO);
	else if (i == total - 1)
		dup2(pipes[i-1][0], STDIN_FILENO);
	else
	{
		dup2(pipes[i-1][0], STDIN_FILENO);
		dup2(pipes[i][1], STDOUT_FILENO);
	}
	for (int j = 0; j < total - 1; j++)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
	}
}

void handle_redirs(t_command_block *cmd)
{
	int	fd;

	for (int i = 0; cmd->input && cmd->input[i]; i++)
	{
		fd = open(cmd->input[i], O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}

	for (int i = 0; cmd->output && cmd->output[i]; i++)
	{
		if (cmd->redir_append)
			fd = open(cmd->output[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(cmd->output[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}
