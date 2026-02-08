#include "../../includes/minishell.h"

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

static int	env_size(t_env *env)
{
	int i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**env_list_to_array(t_env *env)
{
	char	**envp;
	int		i = 0;
	char	*tmp;

	envp = malloc(sizeof(char *) * (env_size(env) + 1));
	if (!envp)
		return (NULL);
	while (env)
	{
		if (env->value)
		{
			tmp = ft_strjoin(env->name, "=");
			envp[i++] = ft_strjoin(tmp, env->value);
			free(tmp);
		}
		else
			envp[i++] = ft_strdup(env->name);
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	*verify_commands(char *cmd, char **paths)
{
	int		i;
	char	*full_path;
	char	*add_slash;

	i = 0;
	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/') && access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	while (paths && paths[i])
	{
		add_slash = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(add_slash, cmd);
		free(add_slash);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

int	execute_cmd(t_cmd_block *cmd, t_env *envp)
{
	char	*path;
	char	**paths;
	char	**env_array;

	if (!cmd->args || !cmd->args[0])
		exit(0);
	paths = find_path(envp);
	path = verify_commands(cmd->args[0], paths);
	if (!path)
	{
		print_error(cmd->args[0], "command not found");
		free(path);
		free_array(paths);
		exit(127);
	}
	if (is_directory(path))
	{
		print_error(path, "Is a directory");
		exit(126);
	}
	env_array = env_list_to_array(envp);
	execve(path, cmd->args, env_array);
	perror("minishell");
	exit(126);
}
