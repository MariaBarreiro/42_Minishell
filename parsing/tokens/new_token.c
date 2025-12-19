#include "tokenizer_minishell.h"

/*
	Get the type and update the current.
*/

void	new_token(t_token **new_token, t_token **head, t_token **current)
{
	(*new_token)->type = get_type((*new_token)->value);
	(*new_token)->next = NULL;

	if(!head)
	{
		*head = *new_token;
		*new_token = *current;
	}
	else
	{
		(*current)->next = *new_token;
		*current = *new_token;
	}
}

/*
	Determine what kind of token a value represents.
*/

t_token_type get_type(char *value)
{
	if (redir_out_token_check("<", value, ft_strlen(value)) == true && value[0])
		return (T_REDIR_OUT);
	else if (redir_append_token_check(">>", value, ft_strlen(value)) == true && value[0])
		return (T_REDIR_APPEND);
	else if (redir_in_token_check("<", value, ft_strlen(value)) == true && value[0])
		return (T_REDIR_IN);
	else if (pipe_token_check("|", value, ft_strlen(value)) == true && value[0])
		return (T_PIPE);
	else if (heredoc_token_check("<<", value, ft_strlen(value)) == true && value[0])
		return (T_HEREDOC);
	else
		return (T_WORD);
}
