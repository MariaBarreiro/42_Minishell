/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlima-si <mlima-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:27:08 by mda-enca          #+#    #+#             */
/*   Updated: 2026/03/15 14:21:17 by mlima-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	Fills token data with the input string.
		Line is the input from the user.
		Return the token created.
*/

t_cmd_block	*tokenizer(t_mini *mini, char *line)
{
	t_token			*token;
	t_cmd_block		*blocks;

	blocks = NULL;
	if (!line[0] || !ft_strcmp(line, "$NOTHING") || check_spaces(line) == 0)
		return (NULL);
	if (!ft_strncmp(line, "$NOTHING", 8))
		line += 8;
	if (!ft_strncmp(line, "\"\"", 2) && (!line[2] || line[2] == ' '))
	{
		print_error(line, "command not found");
		mini->exit_stts = 127;
		return (NULL);
	}
	token = tokenization(mini, line);
	if (!token)
	{
		if (find_unclosed_quote(line))
			print_eof();
		mini->exit_stts = 2;
		return (NULL);
	}
	blocks = parse_blocks(token, mini);
	return (free_tokens(token), blocks);
}

/*
	Alloc memory and call functions for value and type.
*/

t_token	*tokenization(t_mini *mini, char *line)
{
	t_token	*head;
	t_token	*current;
	t_token	*new;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		else
		{
			new = init_token(mini, head, line, &i);
			if (!new)
			{
				free_tokens(head);
				return (NULL);
			}
			new_token(&new, &head, &current);
		}
	}
	return (head);
}

char	find_unclosed_quote(const char *line)
{
	char	quote;
	int		j;

	quote = 0;
	j = 0;
	while (line[j])
	{
		if (!quote && (line[j] == '\'' || line[j] == '"'))
			quote = line[j];
		else if (quote && line[j] == quote)
			quote = 0;
		j++;
	}
	return (quote);
}
