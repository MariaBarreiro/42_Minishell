#include "../header.h"

int	ft_env(t_env *my_env, char **arg)
{
	if (!my_env)
		return (1);
	if (!arg[1])
	{
		while (my_env)
		{
			if (my_env->exported)
			{
				if (my_env->value)
				{
					printf("%s=%s\n", my_env->name, my_env->value);
				}
			}
			my_env = my_env->next;
		}
		return (0);
	}
	else
	{
		write(2, "env: too many arguments\n", 25);
		free (arg);
		return (1);
	}
}
