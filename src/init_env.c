#include "./header.h"

int	init_pwd(t_env **env)
{
	char	cwd[1024];

	if (env_key_exists("PWD", *env))
		return (0);
	if (!getcwd(cwd, sizeof(cwd)))
		return (1);
	update_env("PWD", cwd, env, 1);
	return (0);
}

static char	*compute_shlvl_value(t_env *env)
{
	int		lvl;

	lvl = ft_atoi(get_env_value("SHLVL", env));
	if (lvl >= 999)
	{
		ft_putstr_fd("minishell: warning: shell level too high, resetting to 1\n", 2);
		return (ft_strdup("1"));
	}
	return (ft_itoa(lvl + 1));
}

int	init_shlvl(t_env **env)
{
	char	*value;

	value = compute_shlvl_value(*env);
	if (!value)
		return (1);
	update_env("SHLVL", value, env, 1);
	free(value);
	return (0);
}

int	init_minimal_env(t_env **env)
{
	if (init_pwd(env))
		return (1);
	if (init_shlvl(env))
		return (1);
	return (0);
}

t_env	*init_env(char **envp)
{
	t_env	*head;
	int		i;
	char	*equal;

	head = NULL;
	i = 0;
	while (envp && envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (equal)
			env_add_back(&head, new_node(ft_substr(envp[i], 0, equal - envp[i]),
					ft_strdup(equal + 1)));
		else
			env_add_back(&head, new_node(ft_strdup(envp[i]), NULL));
		i++;
	}
	return (head);
}
