/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlima-si <mlima-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:27:55 by mda-enca          #+#    #+#             */
/*   Updated: 2026/03/13 13:38:36 by mlima-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	set_pwd_env(t_env **env)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (1);
	update_env("PWD", cwd, env, 1);
	if (!get_env_value("OLDPWD", *env))
		update_env("OLDPWD", NULL, env, 1);
	return (0);
}

void	update_shlvl(t_env **env)
{
	int		lvl;
	char	*val;

	val = get_env_value("SHLVL", *env);
	if (!val)
	{
		update_env("SHLVL", "1", env, 1);
		return ;
	}
	lvl = ft_atoi(val) + 1;
	val = ft_itoa(lvl);
	if (!val)
		return ;
	update_env("SHLVL", val, env, 0);
	free(val);
}

int	init_minimal_env(t_env **env)
{
	if (set_pwd_env(env))
		return (1);
	update_shlvl(env);
	update_env("_", "./minishell", env, 1);
	return (0);
}
