#include "../includes/minishell.h"

int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    if (ac != 1 || av[1])
        return (ft_putstr_fd("[Error] Usage: ./minishell\n", 2),127);

    main_loop();
}

void    main_loop(void)
{
    char *input;

    while (1)
    {
        input = readline("minishell");
    }
}
