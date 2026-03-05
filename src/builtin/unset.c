/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlima-si <mlima-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:20:54 by mda-enca          #+#    #+#             */
/*   Updated: 2026/03/05 16:41:55 by mlima-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	append_env(char *key, char *value, t_env **env)
{
	char	*old;
	char	*new;

	old = get_env_value(key, *env);
	if (!old)
		update_env(key, value, env, 1);
	else
	{
		new = ft_strjoin(old, value);
		update_env(key, new, env, 0);
		free(new);
	}
}

static void	remove_key(t_env **my_env, char *args)
{
	t_env	*temp;
	t_env	*prev;

	temp = *my_env;
	prev = NULL;
	while (temp)
	{
		if (!ft_strcmp(temp->name, args))
		{
			if (prev == NULL)
				*my_env = temp->next;
			else
				prev->next = temp->next;
			free(temp->name);
			free(temp->value);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}

static int	valid_identifier(char *s)
{
	int	i;

	i = 0;
	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (0);
	i = 1;
	while (s[i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_unset(t_env **my_env, char **args)
{
	int	i;

	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		if (args[1][0] == '-')
			return (arg_error_unset(args[i]));
		if (valid_identifier(args[i]))
		{
			if (env_key_exists(args[i], *my_env))
				remove_key(my_env, args[i]);
		}
		i++;
	}
	return (0);
}
