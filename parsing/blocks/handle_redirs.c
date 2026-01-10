#include "../parsing_header.h"

/*
	Validate and record an input or output for the current command block.
*/

int	handle_redir(t_cmd_block *block, t_token **token, int type)
{
	char	*filename;
	int		index;

	filename = NULL;
	index = 0;
	(*token) = (*token)->next;
	if (!(*token) || (*token)->type == T_PIPE || (*token)->type == T_REDIR_IN
			|| (*token)->type == T_REDIR_OUT || (*token)->type == T_REDIR_APPEND
			|| (*token)->type == T_HEREDOC)
		return (0);
	if (type == T_REDIR_IN)
	{
		filename = ft_strdup((*token)->value);
		index = block->redir_in;
		block->input[index] = filename;
		block->redir_in += 1;
	}
	else
	{
		if (type == T_REDIR_APPEND)
			block->redir_append += 1;
		filename = ft_strdup((*token)->value);
		index = block->redir_out;
		block->output[index] = filename;
		block->redir_out += 1;
	}
	return (1);
}
int	redir_error(t_cmd_block *head, t_cmd_block *block, t_mini *mini, t_token *token)
{
	write(2, "bash: syntax error near unexpected token ", 41);
	if (!token)
		ft_putendl_fd("`newline'", 2);
	else if (token->type == T_REDIR_IN)
			ft_putendl_fd("`<'", 2);
	else if (token->type == T_REDIR_OUT)
			ft_putendl_fd("`>'", 2);
	else if (token->type == T_PIPE)
			ft_putendl_fd("`|'", 2);
	else if (token->type == T_REDIR_APPEND)
			ft_putendl_fd("`>>'", 2);
	else if (token->type == T_HEREDOC)
			ft_putendl_fd("`<<'", 2);
	free_blocks(head);
	free_blocks(block);
	mini->exit_stts = 2;
	return (0);
}

/*
	Consume the << token.
	Validate the next token as a valid heredoc delimiter.
*/

int	handle_heredoc(t_cmd_block *block, t_token **token)
{
	(*token) = (*token)->next;
	if (!(*token) || (*token)->type == T_PIPE || (*token)->type == T_REDIR_IN
			|| (*token)->type == T_REDIR_OUT || (*token)->type == T_REDIR_APPEND
			||(*token)->type == T_HEREDOC)
		return (0);
	block->limits[block->heredoc++] = ft_strdup((*token)->value);
	return (1);
}

/*
	Handle pipe syntax errors like | ls, ls | ls || wc.
		It cleans up any already-allocated blocks.
		Prints a bash-style error message.
		Sets the shell's exit status to indicate a syntax error
		Returns an error code for the parser to stop.
*/
static int	pipe_error(t_cmd_block *head, t_mini *mini)
{
	free_blocks(head);
	ft_putendl_fd("bash: syntax error near unexpected token `|'", 2);
	mini->exit_stts = 1;
	return (-1);
}
