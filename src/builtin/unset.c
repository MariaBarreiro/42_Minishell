#include "built.h"

	//unset values and attributes of variables and functions >> When you use unset on a variable, it removes the variable 
	//from the shell environment, making it undefined. 
	//This is particularly useful for freeing memory, avoiding accidental variable reuse, and managing temporary variables within scripts.

int	ft_unset(t_env *my_env) //<<<<<<< t_env
{
	if (!my_env)
		return (1);
	printf("under construction, be paciente!!!\n");
	return (0);
}