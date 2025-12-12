#include "tokenizer_minishell.h"

/*
	Main interactive loop for minishell.
	Handles the Read, Evaluate, Print Loop cycle for user interaction.
		Reads input.
		Process commands.
		Manages exit conditions.
*/

void    main_loop(t_shell *shell, char **env)
{
	char	*input_line;
	t_command_block	*blocks;

	while (1)
	{
		if (check_interactive() == true)
			input_line = readline("minishell");
		else
			input_line = get_next_line(STDIN_FILENO);
		if (!input_line)
		{
			if (check_interactive() == true)
				ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (*input_line)
			add_history(input_line);
		blocks = tokenizer(shell, input_line);
	////Acrescentar execucao
		free(input_line);
	}
}
