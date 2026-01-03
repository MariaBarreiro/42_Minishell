#include "../header.h"

char	**find_path(t_env *env)
{
	char	*available_paths;
	char	**my_paths;

	if (!env)
		exit(1);
	while (env && !ft_strnstr(env->name, "PATH=", 5))
		env = env->next;
	if (!env)
		return (NULL);
	available_paths = ft_strdup(env->value);
	if (!available_paths)
		return (NULL);
	my_paths = ft_split(available_paths, ':');
	free (available_paths);
	return (my_paths);
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

char	env_list_to_array(t_env *envp)
{

}
int	execute_cmd(t_cmd_block *cmd, t_env *envp)
{
	char	*plain_path;
	char	*splited_cmd;
	char	**paths;
	char	**env_array;

	splited_cmd = ft_strdup(cmd->args[0]);
	paths = find_path(envp);
	if (!paths)
		exit(1);
	plain_path = verify_commands(splited_cmd, paths);
	if (!plain_path)
	{
		error_not_found(splited_cmd, paths);
		exit(127);
	}
	env_array = env_list_to_array(envp);
	if (execve(plain_path, splited_cmd, envp) == -1)
	{
		perror("pipex");
		free_array(splited_cmd);
		free_array(paths);
		free(plain_path);
		exit(126);
	}
}