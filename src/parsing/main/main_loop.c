/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlima-si <mlima-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:24:49 by mda-enca          #+#    #+#             */
/*   Updated: 2026/03/14 18:36:00 by mlima-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	Main interactive loop for minishell.
	Handles the Read, Evaluate, Print Loop cycle for user interaction.
		Reads input.
		Process commands.
		Manages exit conditions.
*/

/* void	main_loop(t_mini *mini)
{
	char	*input_line;

	while (1)
	{
		input_line = readline("minishell > ");
		if (g_signal)
		{
			mini->exit_stts = g_signal;
			g_signal = 0;
		}
		if (!input_line)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (*input_line)
			add_history(input_line);
		mini->cmd = tokenizer(mini, input_line);
		free(input_line);
		if (!mini->cmd)
			continue ;
		execute_pipeline(mini);
		free_blocks(mini->cmd);
		mini->cmd = NULL;
	}
} */

int	check_interactive(void)
{
	if (isatty(STDIN_FILENO))
		return (1);
	return (0);
}

char	*read_input_line(void)
{
	char	*line;
	char	*trimmed_line;

	if (check_interactive())
		return (readline("minishell > "));
	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (NULL);
	trimmed_line = ft_strtrim(line, "\n");
	free(line);
	return (trimmed_line);
}

void	main_loop(t_mini *mini)
{
	char	*input_line;

	while (1)
	{
		input_line = read_input_line();
		if (!input_line)
		{
			if (check_interactive())
				ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (check_interactive() && *input_line)
			add_history(input_line);
		mini->cmd = tokenizer(mini, input_line);
		free(input_line);
		if (!mini->cmd)
		{
			if (!check_interactive() && mini->exit_stts == 2)
				break ;
			continue ;
		}
		execute_pipeline(mini);
		free_blocks(mini->cmd);
		mini->cmd = NULL;
	}
}
