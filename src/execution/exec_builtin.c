#include "header.h"

int	is_builtin(char **arg)
{
	if (!arg[0])
		return (0);
	if (!ft_strcmp(arg[0], "cd") 
		|| !ft_strcmp(arg[0], "pwd")
		|| !ft_strcmp(arg[0], "echo")
		|| !ft_strcmp(arg[0], "env")
		|| !ft_strcmp(arg[0], "exit")
		|| !ft_strcmp(arg[0], "unset")
		|| !ft_strcmp(arg[0], "export"))
		return (1);
	else 
		return(0);
}

int	exec_builtin(char **arg, t_shell *node)
{
	
	if (ft_strcmp(arg[0], "cd") == 0)
		return (ft_cd(node, arg));
	else if (ft_strcmp(arg[0], "pwd") == 0)
		return (ft_pwd(node, arg));
	else if (ft_strcmp(arg[0], "echo") == 0)
		return (ft_echo(arg));
	else if (ft_strcmp(arg[0], "env") == 0)
		return (ft_env(node, arg));
	else if (ft_strcmp(arg[0], "exit") == 0)
		return (ft_exit(arg));
	else if (ft_strcmp(arg[0], "unset") == 0)
		return (ft_unset(node, arg));
	else if (ft_strcmp(arg[0], "export") == 0)
		return (ft_export(node, arg));
	else 
		return(0);
}
