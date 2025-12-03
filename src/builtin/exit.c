#include "built.h"
/* 	| Caso         | Comportamento                                     |
	| ------------ | ------------------------------------------------- |
	| `exit`       | imprime `exit`, termina com último status         | ok
	| `exit 123`   | imprime `exit`, termina com 123                   |
	| `exit abc`   | imprime `exit` + erro, termina com 2              |
	| `exit 10 20` | imprime `exit` + erro, **não encerra**, retorna 1 | ok
*/

int	is_valid_number(char *arg)
{
	int i = 0;

	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args)
{
	int	exit_code;

	printf("exit\n");
	if (!args[1]);
		exit (g_exit_status);
	if (!is_valid_number(args[1]))
	{
		write(2, "exit: numeric argument required \n", 34);
		exit (2);
	}
	if (args[2])
	{
		printf("exit: too many arguments\n");
		return (1);
	}
	exit_code = (unsigned char)ft_atoll(args[1]);
	exit (exit_code);
}
