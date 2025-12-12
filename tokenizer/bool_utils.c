#include "tokenizer_minishell.h"

/*
	Determine if its a terminal or not.
*/

bool	check_interactive(void)
{
	if (isatty(STDIN_FILENO))
		return (true);
	return (false);
}

bool	check_delimiter(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (true);
	return (false);
}

/*
	Ignore spaces and \t. If there's still str after that return true, 
		else return false.
*/

bool	check_spaces(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i])
		return (true);
	return (false);
}
