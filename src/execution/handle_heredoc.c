#include "../../includes/minishell.h"

static int	get_last_limiter(char **limits)
{
	int	i;

	i = 0;
	while (limits[i + 1])
		i++;
	return (i);
}

static void	write_heredoc(int fd, char *limit)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, limit))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

int	handle_heredocs(t_cmd_block *cmd)
{
	int	fd[2];
	int	i;

	if (!cmd->limits)
		return 1;
	i = get_last_limiter(cmd->limits);
	if (pipe(fd) < 0)
		exit(1);
	write_heredoc(fd[1], cmd->limits[i]);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (0);
}
