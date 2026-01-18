#include "../../includes/minishell.h"

/*
Prints arguments to standard output.
Implements the -n option to suppress the trailing newline character.
Supports expansion of environment variables like $USER within double quotes.
Supports > for redirection, as seen in echo hello > outfile.txt.



the args should come as (attention with spaces):
if echo    marcio   roberto     
	---output:marcio roberto(should ignore spaces)
but if echo "  marcio  roberto   "
	---output:  marcio  roberto  (should print spaces)
or if echo "  marcio  "  "  roberto   "
	---output:  marcio  roberto  (same here)

if echo      -n marcio
	output:marcio(without /n as usual)
but if echo "   -n" "marcio"
	output:   -n marcio(print -n cause it has spaces before the flag)

if the argment has "" i need receive it (without the parentesis)
*/
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
			write (1, &arg[beggin][i], 1);
			i++;
		}
		if (arg[beggin + 1])
			write (1, " ", 1);
		beggin++;
		i = 0;
	}
}

int	ft_echo(char **arg)
{
	int	beggin;
 	if (!arg[1])
	{
		write (1, "\n", 1);
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
		write (1, "\n", 1);
	}
	return (0);
}
