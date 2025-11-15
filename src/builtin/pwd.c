#include "built.h"

//The pwd command executes a program that prints the current working directory, while "echo $PWD" prints the value of the PWD environment variable, 
// which stores the current working directory. Typically, both will give you the same result.

int	ft_is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}
int	ft_pwd(t_env *my_env, char **cmd)
{
	int i;

	i = 0;
	if (cmd[1])
	{
		while (cmd[1][i] && ft_is_space(cmd[1][i]))
			i++;
		if (cmd[1][i] == '-')
		{
			ft_putendl_fd("pwd: options aren't supported", 2);
			return (EXIT_FAILURE);
		}
	}
	while (ft_strncmp(my_env->name, "PWD", 3))
		my_env = my_env->next;
	ft_putendl_fd(my_env->value, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
