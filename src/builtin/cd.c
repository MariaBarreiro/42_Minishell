#include "built.h"

int	ft_cd(char **arg) //<<<<<<< t_env
{
	char	*path;

	if (!arg[1])
	{
		free (arg);
		return (chdir(getenv("HOME")));
	}
	if (arg[2])
	{
		write(2, "cd: too many arguments\n", 24);
		free (arg);
		return (0);
	}
	if (chdir(arg[1]) == -1)
	{
		perror("cd");
		free (arg);
		return (1);
	}
	return (0);
}
