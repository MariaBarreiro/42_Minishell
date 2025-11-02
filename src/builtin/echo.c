/* checklist
Prints arguments to standard output.
Implements the -n option to suppress the trailing newline character.
Supports expansion of environment variables like $USER within double quotes.
Supports > for redirection, as seen in echo hello > outfile.txt.
*/

#include "includes/minishell.h"

int	ft_echo(char **arg)
{
	int	i;
	if (arg[0][0] == '-' && arg[0][1] == 'n')
	{
		i = 1;
		while(arg[++i])
			write(1, arg[i], 1);
	}
	else
		printf("%s\n", arg);
	return (0);
}
