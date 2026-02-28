/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlima-si <mlima-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:19:59 by mda-enca          #+#    #+#             */
/*   Updated: 2026/02/25 17:46:00 by mlima-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_overflow(char *s)
{
	char	*max;
	char	*min;
	int		sign;

	max = "9223372036854775807";
	min = "9223372036854775808";
	sign = 1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s == '0')
		s++;
	if (ft_strlen(s) > 19)
		return (1);
	if (ft_strlen(s) < 19)
		return (0);
	if (sign == 1 && ft_strcmp(s, max) > 0)
		return (1);
	if (sign == -1 && ft_strcmp(s, min) > 0)
		return (1);
	return (0);
}

static int	is_valid_exit_number(char *arg)
{
	int	i;

	i = 0;
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
	if (is_overflow(arg))
		return (0);
	return (1);
}

int	ft_exit(char **args, int exit_stts)
{
	long long	code;

	write(1, "exit\n", 5);
	if (!args[1])
		return (exit_stts);
	if (args[2])
	{
		print_error("exit", "too many arguments");
		return (1);
	}
	if (!strcmp(args[1], "--"))
		return (0);
	if (!is_valid_exit_number(args[1]))
	{
		print_error("exit", "numeric argument required");
		return (2);
	}
	code = ft_atoll(args[1]);
	return ((unsigned char)code);
}
