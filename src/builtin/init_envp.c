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

static int	ft_strsearch(char *str, char c)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

static char *first_part(char *venv)
{
	int	equal;

	equal = ft_strsearch(venv, '=');
	return (ft_substr(venv, 0, equal));
}

static char *second_part(char *venv)
{
	size_t	len;
	int	equal;

	equal = ft_strsearch(venv, '=');
	len = ft_strlen(venv);
	return (ft_substr((const char *)venv, ++equal, len - equal));
}

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*new;
	int		i;
	char	*equal;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (NULL);
		equal = ft_strchr(envp[i], '=');
		if (equal)
		{
			new->name = ft_substr(envp[i], 0, equal - envp[i]);
			new->value = ft_strdup(equal + 1);
		}
		else
		{
			new->name = ft_strdup(envp[i]);
			new->value = NULL;
		}
		new->exported = 1;
		new->next = NULL;
		env_add_back(&head, new);
		i++;
	}
	return (head);
}

