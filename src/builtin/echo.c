#include "../../includes/minishell.h"

static int	has_flag(char *arg)
{
	int i;

	i = 0;
	if (arg[i] == '-')
	{
		i++;
		while(arg[i] && arg[i] == 'n')
			i++;
	}
	if (i > 1 && !arg[i])
		return (1);
	else
		return (0);
}

static void	write_arg(char **arg, int beggin)
{
	int	i;

	i = 0;
	while(arg[beggin])
	{
		while(arg[beggin][i])
		{
			write (STDOUT_FILENO, &arg[beggin][i], 1);
			i++;
		}
		if (arg[beggin + 1])
			write (STDOUT_FILENO, " ", 1);
		beggin++;
		i = 0;
	}
}

int	ft_echo(char **arg)
{
	int	beggin;
 	if (!arg[1])
	{
		write (STDOUT_FILENO, "\n", 1);
		return (0);
	}
 	if (has_flag(arg[1]))
	{
		beggin = 2;
		write_arg(arg, beggin);
	}
	else
	{
		beggin = 1;
		write_arg(arg, beggin);
		write (STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
