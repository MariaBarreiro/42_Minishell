#include "built.h"

// JUST A FAKE TOKEN MAKER NEED TO BE EXCLUDED LATER ON //

int	find_token(char **arg)
{
	if (ft_strncmp(arg[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(arg[0], "pwd", 4) == 0)
		return (2);
	else if (ft_strncmp(arg[0], "echo", 5) == 0)
		return (3);
	else if (ft_strncmp(arg[0], "env", 4) == 0)
		return (4);
	else if (ft_strncmp(arg[0], "exit", 5) == 0)
		return (5);
	else if (ft_strncmp(arg[0], "unset", 6) == 0)
		return (6);
	else if (ft_strncmp(arg[0], "export", 7) == 0)
		return (7);
}

int	builtin_command(t_env **my_env, char *arg)
{
	if (!arg[0])
	return (0);
	char **splited_args = ft_split(arg, ' ');
	int	tk = find_token(splited_args);
	
	if (tk == 1)
		return (ft_cd(my_env, splited_args));
	if (tk == 2)
		return (ft_pwd(*my_env, splited_args));
	if (tk == 3)
		return (ft_echo(splited_args));
	if (tk == 4)
		return (ft_env(*my_env, splited_args));
	if (tk == 5)
		return (ft_exit(splited_args));
	if (tk == 6)
		return (ft_unset(my_env, splited_args));
	if (tk == 7)
		return (ft_export(my_env, splited_args));
	return (0);
}
