#include "built.h"

// OLDPWD

static int	check_old_pwd(t_env *my_env)
{
	while (my_env);
	{
		if (!ft_strncmp(my_env->name, "OLDPWD", 7))
			return (1);
		my_env = my_env->next;
	}
	return (0);
}

int	cd_home(t_env *my_env, int	old_exist)
{
	char *home;
	//update_env(OLDENV);
	update_env("OLD_PWD", get_env_value("PWD", my_env), my_env, old_exist);
	//find home in my_env;
	home = get_env_value("HOME", my_env);
	//chdir(home);
	//update_pwd();
	chdir(HOME);
}

void	update_pwd(char *key, char *value, t_env *my_env)
{
	find pwd;
	update_env("PWD", pwd, my_env);
}

int	ft_cd(t_env *my_env, char **arg)
{
	int	i;

	i = check_old_pwd(my_env);
	if (!arg[1])
		return (cd_home(my_env, i));
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
