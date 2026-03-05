/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlima-si <mlima-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:19:50 by mda-enca          #+#    #+#             */
/*   Updated: 2026/03/05 16:19:00 by mlima-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_env *my_env, char **arg)
{
	if (!my_env)
		return (1);
	if (!arg[1])
	{
		while (my_env)
		{
			if (my_env->exported)
			{
				if (my_env->value)
				{
					printf("%s=%s\n", my_env->name, my_env->value);
				}
			}
			my_env = my_env->next;
		}
		return (0);
	}
	else
	{
		write(2, "env: too many arguments\n", 25);
		return (127);
	}
}
