#include "parsing_header.h"

void	error(t_token *token, char *message, int exit_code)
{
	if (token)
		free_tokens(token);
	ft_putendl_fd(message, 2);
	exit (exit_code);
}
