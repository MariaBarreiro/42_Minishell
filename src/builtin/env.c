#include "built.h"

int	ft_env(char **venv, char *env)
{
	if (!env[3])
	{
		for (int i = 0; venv[i]; i++)
			printf("%s\n", venv[i]);
	}
	return (0);
}