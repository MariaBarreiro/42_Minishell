/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlima-si <mlima-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:07:34 by mlima-si          #+#    #+#             */
/*   Updated: 2025/04/23 12:25:08 by mlima-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*list_a;
	t_list	*list_n;

	list_a = *lst;
	while (list_a)
	{
		list_n = list_a->next;
		ft_lstdelone(list_a, del);
		list_a = list_n;
	}
	*lst = NULL;
}
