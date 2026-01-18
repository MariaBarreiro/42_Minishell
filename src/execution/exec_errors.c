#include "../header.h"

void	error_not_found(char **cmd, char **paths)
{
	ft_putstr_fd("pipex: command not found: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd("\n", 2);
	free_array(cmd);
	free_array(paths);
}

void	free_array(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}