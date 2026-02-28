/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:24:08 by mda-enca          #+#    #+#             */
/*   Updated: 2026/02/18 17:24:09 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	Validate and record an input or output for the current command block.
*/

int	handle_redir(t_cmd_block *block, t_token **token, int type)
{
	(*token) = (*token)->next;
if (type == T_REDIR_OUT && (*token) && (*token)->type == T_PIPE
		&& (*token)->next && (*token)->next->type == T_WORD)
		(*token) = (*token)->next;
	if (!(*token) || (*token)->type == T_PIPE || (*token)->type == T_REDIR_IN
		|| (*token)->type == T_REDIR_OUT || (*token)->type == T_REDIR_APPEND
		|| (*token)->type == T_HEREDOC)
		return (0);
	if (type == T_REDIR_IN)
		return (add_input_redir(block, *token));
	if (type == T_REDIR_APPEND)
		return (add_output_redir(block, *token, type));
	if (type == T_REDIR_OUT)
		return (add_output_redir(block, *token, 0));
	return (0);
}

int	add_input_redir(t_cmd_block *block, t_token *token)
{
	char	*filename;

	filename = ft_strdup(token->value);
	block->last_redir = 0;
	if (!filename)
		return (0);
	block->input[block->redir_in++] = filename;
	return (1);
}

int	add_output_redir(t_cmd_block *block, t_token *token, int append)
{
	t_output	*new_output;
	t_output	*tail;

	new_output = malloc(sizeof(t_output));
	if (!new_output)
		return (0);
	new_output->file = ft_strdup(token->value);
	block->last_redir = 1;
	if (!new_output->file)
		return (free(new_output), 0);
	new_output->append = append;
	new_output->next = NULL;
	if (!block->outputs)
		block->outputs = new_output;
	else
	{
		tail = block->outputs;
		while (tail->next)
			tail = tail->next;
		tail->next = new_output;
	}
	block->n_outputs += 1;
	return (1);
}

int	redir_error(t_cmd_block *head, t_cmd_block *block,
			t_mini *mini, t_token *token)
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
	block->last_redir = 1;
	if (!(*token) || (*token)->type == T_PIPE || (*token)->type == T_REDIR_IN
		|| (*token)->type == T_REDIR_OUT || (*token)->type == T_REDIR_APPEND
		|| (*token)->type == T_HEREDOC)
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
