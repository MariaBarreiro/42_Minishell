#include "../header.h"

void	handle_heredoc(t_cmd_block *cmd)
{
	int		i;
	char	*line;
	int		fd[2];

	i = 0;
	pipe(fd);
	while (cmd->limits && cmd->limits[i])
	{
		while(1)
		{
			line = readline("> ");
			if (!line || !ft_strcmp(line, cmd->limits[i]))
				break;
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
		}
		i++;
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

void	handle_input(t_cmd_block *cmd)
{
	int	i;
	int	fd;

	i = 0;
	while(cmd->input[i])
	{
		fd = open(cmd->input[i], O_RDONLY);
		if (fd < 0)
			exit(1);
		dup2(fd, STDIN_FILENO);
		close(fd);
		i++;
	}
}

static int	open_output_file(t_output *out)
{
	if (out->append)
		return (open(out->file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (open(out->file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}

int	handle_output_redir(t_cmd_block *cmd)
{
	int			fd;
	t_output	*current;

	if (!cmd->outputs)
		return (0);
	current = cmd->outputs;
	while (current)
	{
		fd = open_output_file(current);
		if (fd < 0)
			return (perror(current->file), 1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		current = current->next;
	}
	return (0);
}

void	setup_redirections(t_cmd_block *cmd)
{
	if (cmd->heredoc > 0)
		handle_heredoc(cmd);
	if (cmd->redir_in > 0)
		handle_input(cmd);
	if (cmd->n_outputs > 0)
		handle_output_redir(cmd);
}
