#include "../includes/minishell.h"

int main(int ac, char **av, char  **envp)
{
	t_mini	mini;

    if (ac != 1 || av[1])
        return (ft_putstr_fd("[Error] Usage: ./minishell\n", 2), 127);
    (void)ac;
    (void)av;
	set_signals();
	init_minishell(&mini, envp);
	main_loop(&mini);
	//Missing free_all();
	rl_clear_history();
	return (0);
}
