#include "../../includes/minishell.h"

void	save_fds(t_fd_backup *b)
{
	b->stdin_fd = dup(STDIN_FILENO);
	b->stdout_fd = dup(STDOUT_FILENO);
}

void	restore_fds(t_fd_backup *b)
{
	dup2(b->stdin_fd, STDIN_FILENO);
	dup2(b->stdout_fd, STDOUT_FILENO);
	close(b->stdin_fd);
	close(b->stdout_fd);
}
