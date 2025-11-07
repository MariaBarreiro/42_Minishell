#include "built.h"

/*
Prints arguments to standard output.
Implements the -n option to suppress the trailing newline character.
Supports expansion of environment variables like $USER within double quotes.
Supports > for redirection, as seen in echo hello > outfile.txt.
*/

int	ft_echo(char **arg)
{
	if (arg[1][0] == '-' && arg[1][1] == 'n')
	{
		for(int i = 2; arg[i]; i++)
			printf("%s", arg[i]);
	}
	else
	{
		for(int i = 1; arg[i]; i++)
			printf("%s\n", arg[i]);
	}
	return (0);
}
