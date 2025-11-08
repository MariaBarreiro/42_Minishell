#include "built.h"

int	ft_cd(char *arg)
{
	char *dir = ft_substr(arg, 3, ft_strlen(arg));

	if (!dir[0])
	{
		free(dir);
		return (chdir(getenv("HOME")));
	}
	if (chdir(dir) == -1)
	{
		perror("cd");
		free(dir);
		return (1);
	}
	return (0);
}
