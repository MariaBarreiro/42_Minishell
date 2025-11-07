#include "built.h"

int main(int ac, char **av, char **envp)
{
	if (ac == 40)
		printf("%s\n", envp[0]);
	else 
		return (ft_echo(av));
/* 	for(int i = 0; envp[i]; i++)
		printf("%s\n", envp[i]); */
	return(0);
}