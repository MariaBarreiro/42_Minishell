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

char	**env_list_to_array(t_env *env)
{
	int		i;
	int		count;
	char	**envp;
	char	*tmp;

	count = 0;
	i = 0;
	while (env)
	{
		if (env->exported)
			count++;
		env = env->next;
	}
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	while (env)
	{
		if (env->exported)
		{
			tmp = ft_strjoin(env->name, "=");
			envp[i++] = ft_strjoin(tmp, env->value);
			free(tmp);
		}
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
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	env_array = env_list_to_array(envp);
	execve(path, cmd->args, env_array);
	perror("minishell");
	exit(126);
}
