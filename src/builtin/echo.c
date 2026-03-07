/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlima-si <mlima-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:19:46 by mda-enca          #+#    #+#             */
/*   Updated: 2026/03/04 19:39:20 by mlima-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	has_flag(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
	{
		i++;
		while (arg[i] && arg[i] == 'n')
			i++;
	}
	if (i > 1 && !arg[i])
		return (1);
	else
		return (0);
}

static void	write_arg(char **arg, int start)
{
	int	i;

	i = 0;
	while (arg[start])
	{
		while (arg[start][i])
		{
			write (STDOUT_FILENO, &arg[start][i], 1);
			i++;
		}
		if (arg[start + 1])
			write (STDOUT_FILENO, " ", 1);
		start++;
		i = 0;
	}
}

int	ft_echo(char **arg)
{
	int	start;

	if (!arg[1])
	{
		write (STDOUT_FILENO, "\n", 1);
		return (0);
	}
	start = 1;
	while (arg[start] && has_flag(arg[start]))
		start ++;
	if (start > 1)
		write_arg(arg, start);
	else
	{
		write_arg(arg, start);
		write (STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
