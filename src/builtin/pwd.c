#include "includes/minishell.h"

void	ft_pwd(char **arg, int size)
{
	getcwd(arg[0], size);
}