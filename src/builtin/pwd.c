#include "built.h"

//The pwd command executes a program that prints the current working directory, while "echo $PWD" prints the value of the PWD environment variable, 
// which stores the current working directory. Typically, both will give you the same result.

int	ft_pwd(void)
{
	char	buffer[1024];

	if (getcwd(buffer, sizeof(buffer)) == NULL)
	{
		perror("pwd");
		return (1);
	}
	else
		printf ("%s\n", buffer);
	return (0);
}
