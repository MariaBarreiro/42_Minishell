#include "../../includes/minishell.h"

void	handle_dot(char **args)
{
	if (!ft_strcmp(args[0], "."))
	{
		if (!args[1])
		{
			print_error(args[0], "filename argument required");
			ft_putstr_fd(".: usage: . filename [arguments]\n", STDERR_FILENO);
			exit(2);
		}
	}
	if (!ft_strcmp(args[0], ".."))
	{
		print_error(args[0], "command not found");
		exit(127);
	}
}
