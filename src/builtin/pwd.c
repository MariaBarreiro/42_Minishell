/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlima-si <mlima-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:20:14 by mda-enca          #+#    #+#             */
/*   Updated: 2026/03/05 16:41:36 by mlima-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	arg_error(char *args)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("export", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("-", STDERR_FILENO);
	ft_putchar_fd(args[1], STDERR_FILENO);
	ft_putstr_fd("not a valid identifier", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (2);
}

int	arg_error_unset(char *args)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("unset", STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("-", STDERR_FILENO);
	ft_putchar_fd(args[1], STDERR_FILENO);
	ft_putstr_fd("not a valid identifier", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (2);
}

int	ft_pwd(char **cmd, t_env *env)
{
	char	cwd[4096];

	if (cmd[1] && cmd[1][0] == '-')
	{
		print_error("pwd", "invalid option");
		ft_putstr_fd("pwd: usage: pwd with no options\n", 2);
		return (2);
	}
	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		return (0);
	}
	printf("%s\n", get_env_value("PWD", env));
	return (0);
}
