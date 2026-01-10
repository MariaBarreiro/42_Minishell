#include "../parsing_header.h"

/*
	Get the type and update the current.
*/

void	new_token(t_token **new_node, t_token **head, t_token **current)
{
	(*new_node)->type = get_type((*new_node)->value);
	(*new_node)->next = NULL;

	if(*head == NULL)
	{
		*head = *new_node;
		*current = *new_node;
	}
	else
	{
		(*current)->next = *new_node;
		*current = *new_node;
	}
}

