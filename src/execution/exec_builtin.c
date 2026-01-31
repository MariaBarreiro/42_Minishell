#include "../../includes/minishell.h"

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
		return (0);
}

int	exec_builtin(char **arg, t_mini *mini)
{
	t_env		*my_env;

	my_env = mini->my_env;
	if (ft_strcmp(arg[0], "cd") == 0)
		mini->exit_stts = ft_cd(&my_env, arg);
	else if (ft_strcmp(arg[0], "pwd") == 0)
		mini->exit_stts = ft_pwd(arg, my_env);
	else if (ft_strcmp(arg[0], "echo") == 0)
		mini->exit_stts = ft_echo(arg);
	else if (ft_strcmp(arg[0], "env") == 0)
		mini->exit_stts = ft_env(my_env, arg);
	else if (ft_strcmp(arg[0], "exit") == 0)
		mini->exit_stts = ft_exit(arg, mini->exit_stts);
	else if (ft_strcmp(arg[0], "unset") == 0)
		mini->exit_stts = ft_unset(&my_env, arg);
	else if (ft_strcmp(arg[0], "export") == 0)
		mini->exit_stts = ft_export(&my_env, arg);
	else
		mini->exit_stts = 0;
	return (mini->exit_stts);
}
