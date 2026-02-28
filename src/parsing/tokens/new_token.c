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
