#include "../../../includes/minishell.h"

/*
	Determine if its a terminal or not.
*/

int	check_interactive(void)
{
	return (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO));
}

int	check_delimiter(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

/*
	Ignore spaces and \t. If there's still str after that return true, 
		else return false.
*/

int	check_spaces(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i])
		return (1);
	return (0);
}
