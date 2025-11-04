#include "../includes/minishell.h"

t_shell	*global_sh;

int main(int ac, char **av)
{
	t_shell	shell;

    if (ac != 1 || av[1])
        return (ft_putstr_fd("[Error] Usage: ./minishell\n", 2),127);
    (void)ac;
    (void)av;
    init_shell(&shell);

    main_loop();
}

void    init_shell(t_shell *shell)
{
    shell->input = NULL;
	shell->tokens = NULL;
}

void    main_loop(void)
{
    char *input;

    while (1)
    {
        input = readline("minishell");
		if (!input)
		{
			ft_putstr_fd(("exit"), 2);
			break ;
		}
		add_history(input);
    }
}
