#include "../header.h"

	//unset values and attributes of variables and functions >> When you use unset on a variable, it removes the variable 
	//from the shell environment, making it undefined. 
	//This is particularly useful for freeing memory, avoiding accidental variable reuse, and managing temporary variables within scripts.


/*	
	se for a primeira;
		apenas apagar
	se estiver no meio;
		anterior.next == proxima
		apagar
	se for a ultima; 
		anterior.next == NULL
		apagar
*/

void remove_key(t_env **my_env, char *args)
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
	int i = 0;

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
		return (1);
	i = 1;
	while (args[i])
	{
		if (valid_identifier(args[i]))
		{
			if (env_key_exists(args[i], *my_env))
				remove_key(my_env, args[i]);
		}
		i++;
	}
	return (0);
}
