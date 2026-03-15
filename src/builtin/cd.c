/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlima-si <mlima-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:19:26 by mda-enca          #+#    #+#             */
/*   Updated: 2026/03/15 14:46:43 by mlima-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	update_pwd(char *key, t_env **env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	update_env(key, pwd, env, 0);
	free(pwd);
	return (0);
}

static int	check_old_pwd(t_env *my_env)
{
	while (my_env)
	{
		if (!ft_strcmp(my_env->name, "OLDPWD"))
			return (0);
		my_env = my_env->next;
	}
	return (1);
}

static int	cd_home(t_env **my_env, int create)
{
	char	*home;

	update_env("OLDPWD", get_env_value("PWD", *my_env), my_env, create);
	home = get_env_value("HOME", *my_env);
	if (!home)
	{
		write(2, "cd: HOME not set\n", 18);
		return (1);
	}
	if (chdir(home) == -1)
	{
		perror("cd");
		return (1);
	}
	update_pwd("PWD", my_env);
	return (0);
}

static int	cd_special(t_env **my_env, char *arg)
{
	char	*oldpwd;

	if (!strcmp(arg, "-"))
	{
		oldpwd = get_env_value("OLDPWD", *my_env);
		if (!oldpwd || chdir(oldpwd) == -1)
			return (perror("cd"), 1);
		printf("%s\n", oldpwd);
		update_env("OLDPWD", get_env_value("PWD", *my_env), my_env, 0);
		update_pwd("PWD", my_env);
		return (0);
	}
	else
		return (cd_home(my_env, 0));
	if (chdir(arg) == -1)
		return (perror("cd"), 1);
	update_env("OLDPWD", get_env_value("PWD", *my_env), my_env, 0);
	return (update_pwd("PWD", my_env));
}

int	ft_cd(t_env **my_env, char **arg)
{
	int		create;

	create = check_old_pwd(*my_env);
	if (!arg[1])
		return (cd_home(my_env, create));
	if (arg[2])
	{
		print_error("cd", "too many arguments");
		return (1);
	}
	if (!strcmp(arg[1], "-") || !strcmp(arg[1], "--"))
		return (cd_special(my_env, arg[1]));
	else
	{
		if (chdir(arg[1]) == -1)
		{
			ft_putstr_fd("cd: ", 2);
			perror(arg[1]);
			return (1);
		}
		update_env("OLDPWD", get_env_value("PWD", *my_env), my_env, create);
		return (update_pwd("PWD", my_env));
	}
}
