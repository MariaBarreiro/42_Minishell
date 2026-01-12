#include "../parsing_header.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

/*
	Read line.
	Create history.
	Handle Ctrl + c.
	Call tokenizer.
	Return exit value.
*/

int main(int ac, char **av, char  **envp)
{
	t_mini	mini;

    if (ac != 1 || av[1])
        return (ft_putstr_fd("[Error] Usage: ./minishell\n", 2), 127);
    (void)ac;
    (void)av;
	set_signals();
	init_minishell(&mini, envp);
	//
	main_loop(&mini);
	//Missing free_all();
	rl_clear_history();
	return (0);
}

void	init_minishell(t_mini *mini, char **envp)
{

	mini = malloc(sizeof(t_mini));
	mini->cmd = NULL;
	mini->env = init_env(envp);
	mini->exit_stts = 0;
	//missing.

}
