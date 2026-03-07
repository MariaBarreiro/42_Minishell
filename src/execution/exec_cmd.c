/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:21:30 by mda-enca          #+#    #+#             */
/*   Updated: 2026/02/18 17:21:31 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int	i;

	i = 0;
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
	int		i;
	char	*tmp;

	i = 0;
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
	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
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

	paths = find_path(envp);
	path = verify_commands(cmd->args[0], paths);
	if (!path)
	{
		if (ft_strchr(cmd->args[0], '/'))
			print_error(cmd->args[0], "No such file or directory");
		else
			print_error(cmd->args[0], "command not found");
		free_array(paths);
		exit(127);
	}
	if (!validate_cmd(cmd->args[0], path))
	{
		free(path);
		free_array(paths);
		exit(126);
	}
	env_array = env_list_to_array(envp);
	execve(path, cmd->args, env_array);
	perror("minishell");
	exit(126);
}
