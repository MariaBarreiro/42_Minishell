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

void	cmd_not_found(t_cmd_block *cmd, char **paths)
{
	if (ft_strchr(cmd->args[0], '/'))
		print_error(cmd->args[0], "No such file or directory");
	else
		print_error(cmd->args[0], "command not found");
	free_array(paths);
	exit(127);
}

char	**find_path(t_env *env)
{
	while (env)
	{
		if (env->name && env->value && !ft_strcmp(env->name, "PATH"))
			return (ft_split(env->value, ':'));
		env = env->next;
	}
	return (NULL);
}
