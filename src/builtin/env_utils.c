#include "../../includes/minishell.h"

char	*get_env_value(char *key, t_env *my_env)
{
	while (my_env)
	{
		if (!ft_strncmp(my_env->name, key, ft_strlen(key) + 1))
			return (ft_strdup(my_env->value));
		my_env = my_env->next;
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
	if (value)
		new_var->value = ft_strdup(value);
	else
		new_var->value = NULL;
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
