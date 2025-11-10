#include "built.h"

/*
Prints arguments to standard output.
Implements the -n option to suppress the trailing newline character.
Supports expansion of environment variables like $USER within double quotes.
Supports > for redirection, as seen in echo hello > outfile.txt.



fix  >>>> -nnnnn
deal with spaces
int	has_flag(char *arg)
{
	int i;

	i = 0;
	if (arg[i++] == '-')
	{
		while(arg[i] == 'n')
			i++;
	}
	if (!arg[i])
		return (1);
	else
		return (0);
}
*/

int	ft_echo(char **arg)
{
	//int i = 5;
	//int flag = has_flag(arg[1]);
	if (!arg[1][0])
		return (0);
	printf ("ehco echo echo");
/* 	if (arg[1][i] == '-' && arg[1][i + 1] == 'n')
	{
		i += 2;
		while (arg[1][i++])
			write (1, &arg[][i], 1);
	}
	else
	{
		while (arg[1][i])
			write (1, &arg[1][i++], 1);
		write (1, "\n", 1);
	} */
	return (0);
}
