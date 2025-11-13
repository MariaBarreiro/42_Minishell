#include "built.h"

static int	has_value(char **venv)
{
	int	i, j;
	int flag;

	i = 0;
	while(venv[i])
	{
		j = 0;
		while(venv[i][j] != "=" && venv[i][j])
			j++;
		if (venv[i][j] == "=")
			return (1);
		i++;
	}
	return (0);
}

static char *first_part(char *venv)
{
	int		i;

	i = 0;
	while(venv[i])
	{
		if (venv[i] == "=")
			return (ft_substr(venv, 0, i));
		i++;
	}
	return (NULL);
}

static char *second_part(char *venv)
{
	int		i;

	i = 0;
	while(venv[i])
	{
		if (venv[i] == "=")
			return (ft_strdup(venv[++i]));
		i++;
	}
	return (NULL);
}

t_env	*init_env(char **venv)
{
	int	i;
	t_env	temp;

	i = 1;
	while(venv[i])
	{
		if (has_value(venv[i]))
		{
			temp.name  = first_part(venv[i]);
			temp.value = second_part(venv[i]);
		}
		else
		{
			temp.name  = first_part(venv[i]);
			temp.value = NULL;
		}
		temp.exported = 1;
		i++;
	}
}