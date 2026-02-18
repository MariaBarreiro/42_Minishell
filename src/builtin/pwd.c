/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:20:14 by mda-enca          #+#    #+#             */
/*   Updated: 2026/02/18 17:20:16 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
