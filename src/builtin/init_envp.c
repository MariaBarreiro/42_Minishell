#include "built.h"

/* static int	has_value(char **venv)
{
	int	i, j;

	i = 0;
	while(venv[i])
	{
		j = 0;
		while(venv[i][j] != '=' && venv[i][j])
			j++;
		if (venv[i][j] == '=')
			return (1);
		i++;
	}
	return (0);
} */

t_env	*init_env(char **envp)
{
	t_env	*head;
	int		i;
	char	*equal;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (equal)
			env_add_back(&head, new_node
				(ft_substr(envp[i], 0, equal - envp[i]), ft_strdup(equal + 1)));
		else
			env_add_back(&head, new_node(ft_strdup(envp[i]), NULL));
		i++;
	}
	return (head);
}

