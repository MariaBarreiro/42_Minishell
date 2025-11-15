#include "built.h"

int	ft_cd(t_env *my_env, char **arg)
{
	char home;

	while (ft_strncmp(my_env->name, "HOME", 4))
		my_env = my_env->next;
	home = ft_strdup(my_env->value);
	if (!arg[1])
	{
		while (ft_strncmp(my_env->name, "PWD", 3))
			my_env = my_env->next;
		my_env->value = ft_strdup(home);
		free (arg);
		return (chdir(getenv("HOME")));
	}
	if (arg[2])
	{
		write(2, "cd: too many arguments\n", 24);
		free (arg);
		return (0);
	}
	if (chdir(arg[1]) != -1)
	{
		while (ft_strncmp(my_env->name, "PWD", 3))
			my_env = my_env->next;
		my_env->value = ft_strdup(arg[1]);
		free (arg);
		return (0);
	}
	perror("cd");
	free (arg);
	return (1);
}
