/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 14:03:44 by mda-enca          #+#    #+#             */
/*   Updated: 2026/03/15 14:03:45 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*join_fragment(char *word, char *fragment)
{
	char	*temp;

	temp = word;
	if (word)
		word = ft_strjoin(word, fragment);
	else
		word = ft_strdup(fragment);
	free(temp);
	return (word);
}

char	*expand_fragment(t_mini *mini, char *fragment, char quote_type,
		int expand)
{
	if (!expand)
		return (fragment);
	fragment = tilde_fragment(mini, fragment, quote_type);
	return (var_expansion(mini, fragment, quote_type));
}

char	*expand_fragment(t_mini *mini, char *fragment, char quote_type,
		int expand)
{
	if (!expand)
		return (fragment);
	fragment = tilde_fragment(mini, fragment, quote_type);
	return (var_expansion(mini, fragment, quote_type));
}
