#include "../../../includes/minishell.h"

/*
	Main interactive loop for minishell.
	Handles the Read, Evaluate, Print Loop cycle for user interaction.
		Reads input.
		Process commands.
		Manages exit conditions.
*/

char	*read_input_line(void)
{
	if (check_interactive() == 1)
		return (readline("minishell > "));
	return (get_next_line(STDIN_FILENO));
}

void	main_loop(t_mini *mini)
{
	char		*input_line;
	int			ret;

	while (1)
	{
		input_line = read_input_line();
		if (!input_line)
		{
			if (check_interactive() == 1)
				ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (*input_line)
			add_history(input_line);
		mini->cmd = tokenizer(mini, input_line);
		ret = execute_pipeline(mini);
		if (mini->cmd)	
			free_blocks(mini->cmd);
		free(input_line);
		mini->exit_stts = ret;
	}
}
