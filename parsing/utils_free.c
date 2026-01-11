#include "parsing_header.h"

void	free_tokens(t_token *token)
{
	t_token *temp;

	while (token)
	{
		temp = token->next;
		if (token->value)
			free(token->value);
		free(token);
		token = temp;
	}
}
