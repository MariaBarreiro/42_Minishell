/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlima-si <mlima-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:28:53 by mda-enca          #+#    #+#             */
/*   Updated: 2026/02/28 17:07:11 by mlima-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_tokens(t_token *token)
{
	t_token	*temp;

	while (token)
	{
		temp = token->next;
		if (token->value)
			free(token->value);
		free(token);
		token = temp;
	}
}

void	free_env_list(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		free(env->name);
		free(env->value);
		free(env);
		env = next;
	}
}
