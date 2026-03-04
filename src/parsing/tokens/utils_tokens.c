/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:27:11 by mda-enca          #+#    #+#             */
/*   Updated: 2026/02/18 17:27:12 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_exact_token(const char *token, const char *value, long len)
{
	int	match;

	if ((size_t)len != ft_strlen(token))
		return (0);
	match = ft_strncmp(token, value, len);
	if (match == 0)
		return (1);
	return (0);
}

int	is_double_redirect(const char *line, int *i)
{
	if ((line[*i] == '>' && line[1 + *i] == '>')
		|| (line[*i] == '<' && line[1 + *i] == '<'))
		return (1);
	return (0);
}

char	*extract_quoted_fragment(const char *line, int *i, char *quote_type)
{
	int		start_word;
	char	*fragment;

	*quote_type = line[(*i)++];
	start_word = (*i);
	while (line[*i] && line[*i] != *quote_type)
		(*i)++;
	if (line[*i] != *quote_type)
		return (NULL);
	fragment = ft_substr(line, start_word, (*i - start_word));
	(*i)++;
	return (fragment);
}

char	*extract_unquoted_fragment(const char *line, int *i)
{
	int		start_word;
	char	*fragment;

	start_word = (*i);
	while (line[*i] && check_delimiter(line[*i]) == 0 && line[*i] != '"'
		&& line[*i] != ' ' && line[*i] != '\t' && line[*i] != '\'')
		(*i)++;
	fragment = ft_substr(line, start_word, (*i - start_word));
	return (fragment);
}

int	is_heredoc_limiter(const char *line, int i)
{
	while (i > 0 && (line[i - 1] == ' ' || line[i - 1] == '\t'))
		i--;
	if (i > 1 && line[i - 1] == '<' && line[i - 2] == '<')
		return (1);
	return (0);
}

