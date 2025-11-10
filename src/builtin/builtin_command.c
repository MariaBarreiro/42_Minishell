#include "built.h"

int	find_token(char **arg)
{
	int i = 0;
	char *cd = "cd";
	char *pwd = "pwd";
	char *echo = "echo";
	char *env = "env";
	char *exit = "exit";

	while (arg[0][i] == cd[i] && arg[0][i])
		i++;
	if (!cd[i])
		return (1);

	i = 0;
	while (arg[0][i] == pwd[i] && arg[0][i])
		i++;
	if (!pwd[i])
		return (2);

	i = 0;
	while (arg[0][i] == echo[i] && arg[0][i])
		i++;
	if (!echo[i])
		return (3);

	i = 0;
	while (arg[0][i] == env[i] && arg[0][i])
		i++;
	if (!env[i])
		return (4);

	i = 0;
	while (arg[0][i] == exit[i] && arg[0][i])
		i++;
	if (!exit[i])
		return (5);
	return (0);
}

int	builtin_command(char **venv, char *arg)
{
	if (!arg[0])
		return (0);
	char **splited_args = ft_split(arg, ' ');
	int	tk = find_token(splited_args);

	if (tk == 1)
		return (ft_cd(splited_args));
	if (tk == 2)
		return (ft_pwd());
	if (tk == 3)
		return (ft_echo(splited_args));
	if (tk == 4)
		return (ft_env(venv, splited_args));
	if (tk == 5)
		return (ft_exit());
	return (0);
}
