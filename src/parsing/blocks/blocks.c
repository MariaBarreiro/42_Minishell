#include "../../../includes/minishell.h"

t_cmd_block	*parse_blocks(t_token *token, t_mini *mini)
{
	int				total_ac;
	t_cmd_block		*block[3];

	block[0] = NULL;
	block[1] = NULL;

	while (token)
	{
		total_ac  = count_ac(token);
		block[2] = new_block(total_ac);
		if (!block[2])
			return (NULL);
		if (fill_block(block[2], &token, mini, block[0]) != true)
			return (NULL);
		if (!block[0])
			block[0] = block[2];
		else
			block[1]->next = block[2];
		block[1] = block[2];
		if (token && token->type == T_PIPE)
		{
			token = token->next;
			if (!token || token->type == T_PIPE)
				return (pipe_error(block[0], mini), NULL);
		}
	}
	return (block[0]);
}

/*
	Allocate and initialize the new t_cmd_block structure to represent one command
		in the pipeline, complete with arrays for its arguments and redirections.
*/

t_cmd_block *new_block(int ac)
{
	t_cmd_block	*new_block;

	new_block = ft_calloc(1, sizeof(t_cmd_block));
	if (!new_block)
		return NULL;

	new_block->args = ft_calloc((ac + 1), sizeof(char *));
	new_block->limits = ft_calloc((ac + 1), sizeof(char *));
	new_block->input = ft_calloc((ac + 1), sizeof(char *));
//	new_block->next = NULL;
	return (new_block);
}

/*
	Consume tokens up to the next pipe and populate a single t_cmd_block.	
*/
int	fill_block(t_cmd_block *block, t_token **token, t_mini *mini, t_cmd_block *head)
{
	int	i;

	i = 0;
	while (*token && (*token)->type != T_PIPE)
	{
		if ((*token)->type == T_WORD)
			block->args[i++] = ft_strdup((*token)->value);
		else if ((*token)->type == T_REDIR_IN || (*token)->type == T_REDIR_OUT 
					|| (*token)->type == T_REDIR_APPEND)
		{
			if (handle_redir(block, token, (*token)->type) == 0)
				return (redir_error(head, block, mini, *token), false);
		}
		else if ((*token)->type == T_HEREDOC)
		{
			if (handle_heredoc(block, token) == false)
				return (redir_error(head, block, mini, *token), false);
		}
	(*token) = (*token)->next;
	}
	block->args[i] = NULL;
	return (true);
}
