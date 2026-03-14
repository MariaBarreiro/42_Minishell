/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlima-si <mlima-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:27:59 by mda-enca          #+#    #+#             */
/*   Updated: 2026/03/14 18:37:05 by mlima-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_mini	mini;

	if (ac != 1 || av[1])
		return (ft_putstr_fd("[Error] Usage: ./minishell\n", 2), 127);
	(void)ac;
	(void)av;
	set_signals();
	init_minishell(&mini, envp);
	main_loop(&mini);
	free_env_list(mini.my_env);
	rl_clear_history();
	return (mini.exit_stts);
}
