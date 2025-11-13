#include "built.h"

int	ft_env(t_env *venv, char **env) //<<<<<<< t_env
{
	int	i;

	if (!env[1])
	{
		while (venv->next)
		{
			if (venv->exported)
			{
				if (venv->value)
				{
					printf("%s=", venv->name);
					printf("%s\n", venv->value);
				}
			}
			venv = venv->next;
		}
	}
	else
	{
		write(2, "env: too many arguments\n", 25);
		free (env);
		return (1);
	}
}
