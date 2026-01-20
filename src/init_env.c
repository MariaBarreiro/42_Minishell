#include "../../../includes/minishell.h"

int	set_pwd_env(t_env **env)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (1);
	update_env("PWD", cwd, env, 1);
	if (!get_env_value("OLDPWD", *env))
		update_env("OLDPWD", NULL, env, 1);
	return (0);
}

static void	update_shlvl(t_env **env)
{
	int		lvl;
	char	*val;

	val = get_env_value("SHLVL", *env);
	if (!val)
	{
		update_env("SHLVL", "1", env, 1);
		return ;
	}
	lvl = ft_atoi(val) + 1;
	val = ft_itoa(lvl);
	if (!val)
		return ;
	update_env("SHLVL", val, env, 1);
	free(val);
}

int	init_minimal_env(t_env **env)
{
	if (set_pwd_env(env))
		return (1);
	update_shlvl(env);
	return (0);
}

/*t_env	*init_env(char **envp)
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
}*/
