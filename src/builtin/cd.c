#include "includes/minishell.h"

void	ft_cd(char **arg)
{
	chdir(arg[0]);
}