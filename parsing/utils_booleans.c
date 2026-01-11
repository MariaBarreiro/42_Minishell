#include "parsing_header.h"

/*
	Determine if its a terminal or not.
*/

int	check_interactive(void)
{
	if (isatty(STDIN_FILENO))
		return (1);
	return (0);
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

int	is_exact_token(const char *token, const char *value, long len)
{
	int	match;

	if (len != ft_strlen(token))
		return (0);
	match = ft_strncmp(token, value, len);
	if (match == 0)
		return 1;
	return 0;
}
