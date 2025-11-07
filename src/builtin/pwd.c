#include "built.h"

//The pwd command executes a program that prints the current working directory, while "echo $PWD" prints the value of the PWD environment variable, 
// which stores the current working directory. Typically, both will give you the same result.

void	ft_pwd(char **arg, int size)
{
	getcwd(arg[0], size);
}