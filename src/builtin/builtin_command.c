#include "built.h"

int	find_token(char *arg)
{
	int i = 0;
	char *cd = "cd";
	char *pwd = "pwd";
	char *echo = "echo";

	while (arg[i] == cd[i] && arg[i])
		i++;
	if (!cd[i])
		return (1);

	i = 0;
	while (arg[i] == pwd[i] && arg[i])
		i++;
	if (!pwd[i])
		return (2);

	i = 0;
	while (arg[i] == echo[i] && arg[i])
		i++;
	if (!echo[i])
		return (3);
	return (0);
}
int	builtin_command(char *arg)
{
	int	tk = find_token(arg);

	if (tk == 1)
		return (ft_cd(arg));
	if (tk == 2)
		return (ft_pwd());
	if (tk == 3)
		return (ft_echo(arg));
	return (0);
}