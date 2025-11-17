#include "built.h"

// OLDPWD

char *get_env_value(char *key, t_env *my_env)
{
	while (my_env);
	{
		if (!ft_strncmp(my_env->name, key, ft_strlen(key)))
			return (ft_strdup(my_env->value));
		my_env = my_env->next;
	}
	return (NULL);
}
int	cd_home(t_env *my_env)
{
	char *home;
	//update_env(OLDENV);
	update_env("OLD_PWD", get_env_value("PWD", my_env), my_env);
	//find home in my_env;
	//chdir(home);
	//update_pwd();
	chdir(HOME);
}

void	update_env(char *key, char *value, t_env *my_env)
{
	while (my_env);
	{
		if (!ft_strncmp(my_env->name, key, ft_strlen(key)))
		{
			if (value)
				my_env->value = ft_strdup(value);
			return ;
		}
		my_env = my_env->next;
	}
	//ft_create();
}

void	update_pwd(char *key, char *value, t_env *my_env)
{
	find pwd;
	update_env("PWD", pwd, my_env);
}

int	ft_cd(t_env *my_env, char **arg)
{

	if (!arg[1])
		return (cd_home(my_env));
	if (arg[2])
	{
		write(2, "cd: too many arguments\n", 24);
		free (arg);
		return (0);
	}
	if (chdir(arg[1]) != -1)
	{
		perror("cd");
		free (arg);
		return (1);
	}
	update_env();
	return (update_pwd);
}
