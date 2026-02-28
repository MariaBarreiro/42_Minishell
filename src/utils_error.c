/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlima-si <mlima-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:28:50 by mda-enca          #+#    #+#             */
/*   Updated: 2026/02/28 17:08:50 by mlima-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	error(t_token *token, char *message, int exit_code)
{
	if (token)
		free_tokens(token);
	ft_putendl_fd(message, 2);
	exit (exit_code);
}

static void	free_env(t_env *lst)
{
	t_env	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst->next;
		free(lst->name);
		if (lst->value)
			free(lst->value);
		free(lst);
		lst = tmp;
	}
}

void	free_all(t_mini *mini)
{
	if (mini->my_env)
		free_env(mini->my_env);
	if (mini->cmd)
		free_blocks(mini->cmd);
}
