#include "../../includes/minishell.h"

static int	has_plus_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '+' && s[i + 1] == '=')
			return (1);
		if (s[i] == '=')
			return (0);
		i++;
	}
	return (0);
}

static int	valid_identifier(char *s)
{
	int	i;

	if (!s || !s[0])
		return (0);
	if (!ft_isalpha(s[0]) && s[0] != '_')
	{
		print_error("export", "not a valid identifier");
		return (0);
	}
	i = 1;
	while (s[i])
	{
		if (s[i] == '+' && s[i + 1] == '=')
			return (1);
		if (s[i] == '=')
			return (1);
		if (!ft_isalnum(s[i]) && s[i] != '_')
		{
			print_error("export", "not a valid identifier");
			return (0);
		}
		i++;
	}
	return (1);
}

char	*get_key(char *args)
{
	int	equal;

	equal = ft_strsearch(args, '=');
	if (equal == -1)
		return (ft_strdup(args));
	return (ft_substr(args, 0, equal));
}

static char	*get_value(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '+' && s[i + 1] == '=')
			return (ft_strdup(s + i + 2));
		if (s[i] == '=')
			return (ft_strdup(s + i + 1));
		i++;
	}
	return (NULL);
}

int	ft_export(t_env **my_env, char **args)
{
	int		i;
	char	*key;
	int		rt;
	char	*value;

	rt = 0;
	if (!args[1])
		return (print_variables(*my_env));
	i = 1;
	while (args[i])
	{
		if (!valid_identifier(args[i]))
			rt = 1;
		else
		{
			key = get_key(args[i]);
			value = get_value(args[i]);
			if (has_plus_equal(args[i]))
				append_env(key, value, my_env);
			else
				update_env(key, value, my_env, env_key_exists(key, *my_env));
		}
		i++;
	}
	return (rt);
}
