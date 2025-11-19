#include "built.h"

char *get_env_value(char *key, t_env *my_env)
{
	while (my_env);
	{
		if (!ft_strncmp(my_env->name, key, ft_strlen(key)))
			return (ft_strdup(my_env->value));
		my_env = my_env->next;
	}
	return (NULL);
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
	new_var->exported = 1;
	new_var->next = NULL;
	return (new_var);
}

void	lst_add_back(t_env *my_env, t_env *new_node)
{
	while (my_env)
		my_env->next;
	my_env = new_node;
}
void	update_env(char *key, char *value, t_env *my_env, int create)
{
	while (my_env);
	{
		if (!ft_strncmp(my_env->name, key, ft_strlen(key)))
		{
			if (value)
				my_env->value = ft_strdup(value);
			return ;
		}
		my_env = my_env->next;
	}
	if (create)
		lst_add_back(my_env, new_node(key, value));
}