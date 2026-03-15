/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlima-si <mlima-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:19:53 by mda-enca          #+#    #+#             */
/*   Updated: 2026/03/15 14:04:20 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(char *name, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->name, name))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	env_key_exists(char *key, t_env *my_env)
{
	while (my_env)
	{
		if (!ft_strcmp(my_env->name, key))
			return (1);
		my_env = my_env->next;
	}
	return (0);
}

t_env	*new_node(char *key, char *value)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
		return (NULL);
	new_var->name = ft_strdup(key);
	if (!new_var->name)
		return (free(new_var), NULL);
	if (value)
		new_var->value = ft_strdup(value);
	else
		new_var->value = NULL;
	if (value && !new_var->value)
		return (free(new_var->name), free(new_var), NULL);
	new_var->exported = 1;
	new_var->next = NULL;
	return (new_var);
}

void	lst_add_back(t_env **my_env, t_env *new_node)
{
	t_env	*tmp;

	if (!my_env || !new_node)
		return ;
	if (*my_env == NULL)
	{
		*my_env = new_node;
		return ;
	}
	tmp = *my_env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

void	update_env(char *key, char *value, t_env **my_env, int create)
{
	t_env	*tmp;

	tmp = *my_env;
	if (create)
	{
		lst_add_back(my_env, new_node(key, value));
		return ;
	}
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, key, ft_strlen(key) + 1))
		{
			if (value)
			{
				free(tmp->value);
				tmp->value = ft_strdup(value);
			}
			return ;
		}
		tmp = tmp->next;
	}
}
