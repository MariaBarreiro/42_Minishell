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
	Get the type and update the current.
*/

void	new_token(t_token **new_node, t_token **head, t_token **current)
{
	if (!(*new_node)->quoted)
		(*new_node)->type = get_type((*new_node)->value);
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
