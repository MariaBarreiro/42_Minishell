/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:27:05 by mda-enca          #+#    #+#             */
/*   Updated: 2026/02/18 17:27:06 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	Append token to the linked list and update current tail.
*/

void	new_token(t_token **new_node, t_token **head, t_token **current)
{
	(*new_node)->next = NULL;
	if (*head == NULL)
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

char	*tilde_fragment(t_mini *mini, char *fragment, char quote_type)
{
	char	*home;
	char	*expanded;

	if (quote_type || fragment[0] != '~')
		return (fragment);
	if (fragment[1] != '\0' && fragment[1] != '/')
		return (fragment);
	home = get_env_value("HOME", mini->my_env);
	if (!home)
		return (fragment);
	expanded = ft_strjoin(home, fragment + 1);
	free(home);
	if (!expanded)
		return (fragment);
	free(fragment);
	return (expanded);
}
