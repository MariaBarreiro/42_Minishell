/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 12:57:23 by mda-enca          #+#    #+#             */
/*   Updated: 2026/03/15 12:58:06 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	count_unquoted_fields(char *value)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (value && value[i])
	{
		while (value[i] == ' ' || value[i] == '\t')
			i++;
		if (!value[i])
			break ;
		count++;
		while (value[i] && value[i] != ' ' && value[i] != '\t')
			i++;
	}
	return (count);
}

void	add_unquoted_fields(char **args, int *i, char *value)
{
	int		start;
	int		end;
	char	*field;

	start = 0;
	end = 0;
	field = 0;
	while (value && value[start])
	{
		while (value[start] == ' ' || value[start] == '\t')
			start++;
		if (!value[start])
			break ;
		end = start;
		while (value[end] && value[end] != ' ' && value[end] != '\t')
			end++;
		field = ft_substr(value, start, end - start);
		args[(*i)++] = field;
		start = end;
	}
}

int	process_block_token(t_cmd_block *block, t_token **token, int *i)
{
	if ((*token)->type == T_WORD && ((*token)->value[0] != '\0'
			|| (*token)->quoted))
	{
		if ((*token)->quoted)
			block->args[(*i)++] = ft_strdup((*token)->value);
		else
			add_unquoted_fields(block->args, i, (*token)->value);
	}
	else if ((*token)->type == T_REDIR_IN || (*token)->type == T_REDIR_OUT
		|| (*token)->type == T_REDIR_APPEND)
		return (handle_redir(block, token, (*token)->type));
	else if ((*token)->type == T_HEREDOC)
		return (handle_heredoc(block, token));
	return (1);
}
