#include "built.h"

/*
Prints arguments to standard output.
Implements the -n option to suppress the trailing newline character.
Supports expansion of environment variables like $USER within double quotes.
Supports > for redirection, as seen in echo hello > outfile.txt.
*/

int	ft_echo(char *arg)
{
	int i = 5;
	if (!arg[4])
		return (0);
	if (arg[i] == '-' && arg[i + 1] == 'n')
	{
		i += 2;
		while (arg[i++])
			write (1, &arg[i], 1);
	}
	else
	{
		while (arg[i])
			write (1, &arg[i++], 1);
		write (1, "\n", 1);
	}
	return (0);
}
