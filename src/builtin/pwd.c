#include "../../includes/minishell.h"

//The pwd command executes a program that prints the current working directory, while "echo $PWD" prints the value of the PWD environment variable, 
// which stores the current working directory. Typically, both will give you the same result.

int	ft_pwd(void)
{
	char	buffer[1024];

	if (getcwd(buffer, sizeof(buffer)) == NULL)
	{
		perror("PWD");
		return (1);
	}
	else
		printf ("%s\n", buffer);
	return (0);
}

/* 	int i;

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
if (my_env)
	ft_putendl_fd(my_env->value, STDOUT_FILENO);
return (EXIT_SUCCESS); */
