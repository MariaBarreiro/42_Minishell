#include "../../../includes/minishell.h"

t_env	*build_env_node(const char *entry)
{
	char	*equal;
	char	*key;
	char	*value;

	equal = ft_strchr(entry, '=');
	if (!equal)
		return (add_new_node(ft_strdup(entry), NULL));
	key = ft_substr(entry, 0, equal - entry);
	value = ft_strdup(equal + 1);
	if (!key || !value)
	{
		free(key);
		free(value);
		return (NULL);
	}
	return (add_new_node(key, value));
}

t_env	*add_new_node(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (free(key), free(value), NULL);
	node->name = key;
	node->value = value;
	node->exported = 1;
	node->next = NULL;
	return (node);
}

void	list_add_back(t_env **env, t_env *new_node)
{
	t_env	*tail;

	if (!env || !new_node)
		return ;
	if (!*env)
	{
		*env = new_node;
		return ;
	}
	tail = *env;
	while (tail->next)
		tail = tail->next;
	tail->next = new_node;
}

/* t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*node;
	int		i;

	head = NULL;
	i = 0;
	while (envp && envp[i])
	{
		node = build_env_node(envp[i++]);
		if (node)
			list_add_back(&head, node);
	}
	return (head);
} */
