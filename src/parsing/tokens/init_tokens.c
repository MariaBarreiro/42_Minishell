/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:26:59 by mda-enca          #+#    #+#             */
/*   Updated: 2026/02/18 17:27:00 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	If it's delimiter create a token, else get the value.
		start is the head of the linked list.
*/

t_token	*init_token(t_mini *mini, t_token *head, char *line, int *i)
{
	t_token	*new;

	new = calloc(sizeof(t_token), 1);
	if (!new)
		error(head, "Error: failed in memory allocate\n", 1);
	set_token_value(mini, new, line, i);
	if (!new->value)
	{
		free_tokens(head);
		free(new);
		return (NULL);
	}
	if (new->quoted)
		new->type = T_WORD;
	else
		new->type = get_type(new->value);
	return (new);
}

void	set_token_value(t_mini *mini, t_token *new, char *line, int *i)
{
	if (is_double_redirect(line, i))
	{
		new->value = ft_substr(line, *i, 2);
		*i += 2;
		return ;
	}
	if (check_delimiter(line[*i]) == 1)
	{
		new->value = ft_substr(line, *i, 1);
		*i += 1;
		return ;
	}
	new->quoted = 0;
	new->value = get_tokens(mini, line, i, &new->quoted,
			!is_heredoc_limiter(line, *i));
}

/*
	Determine what kind of token a value represents.
*/

t_token_type	get_type(char *value)
{
	long	len;

	len = ft_strlen(value);
	if (is_exact_token(">>", value, len) == 1 && value[0])
		return (T_REDIR_APPEND);
	if (is_exact_token("<<", value, len) == 1 && value[0])
		return (T_HEREDOC);
	if (is_exact_token("<", value, len) == 1 && value[0])
		return (T_REDIR_IN);
	if (is_exact_token(">", value, len) == 1 && value[0])
		return (T_REDIR_OUT);
	if (is_exact_token("|", value, len) == 1 && value[0])
		return (T_PIPE);
	return (T_WORD);
}

/*
	Word constructor!
		Builds one word at a time!
*/

char	*get_tokens(t_mini *mini, const char *line, int *i, int *quoted, int expand)
{
	char	*word;
	char	*fragment;
	char	*temp;
	int		was_quoted;

	word = NULL;
	while (line[*i] && line[*i] != ' '
		&& line[*i] != '\t' && check_delimiter(line[*i]) == 0)
	{
		was_quoted = 0;
		fragment = get_single_token(mini, line, i, &was_quoted, expand);
		if (!fragment)
			return (free(word), NULL);
		if (was_quoted)
			*quoted = 1;
		temp = word;
		if (word)
			word = ft_strjoin(word, fragment);
		else
			word = ft_strdup(fragment);
		free(temp);
		free(fragment);
	}
	return (word);
}

/*
	Fragment extractor.
*/

char	*get_single_token(t_mini *mini, const char *line, int *i, int *quoted, int expand)
{
	char	quote_type;
	char	*fragment;

	quote_type = 0;
	if (line[*i] == '$' && (line[*i + 1] == '"' || line[*i + 1] == '\''))
		(*i)++;
	if (line[*i] == '\'' || line[*i] == '"')
	{
		*quoted = 1;
		fragment = extract_quoted_fragment(line, i, &quote_type);
	}
	else
		fragment = extract_unquoted_fragment(line, i);
	if (!fragment)
		return (NULL);
	if (!expand)
		return (fragment);
	return (var_expansion(mini, fragment, quote_type));
}
