#include "built.h"

int	ft_env(char **venv, char **env)
{
	int	i;

	if (!env[1])
	{
		i = 0;
		while (venv[i])
		{
			printf("%s\n", venv[i]);
			i++;
		}
		free (env);
		return (0);
	}
	else
	{
		write(2, "env: too many arguments\n", 25);
		free (env);
		return (1);
	}
}
