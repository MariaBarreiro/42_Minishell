#include "../includes/minishell.h"
#include <signal.h>

t_shell	*global_sh;

int main(int ac, char **av)
{
	t_shell	*shell;

    if (ac != 1 || av[1])
        return (ft_putstr_fd("[Error] Usage: ./minishell\n", 2),127);
    (void)ac;
    (void)av;
    shell = NULL;
	shell = init_shell(shell);
	global_sh = shell;
	set_signals();


    main_loop();
}

void    init_shell(t_shell *shell)
{
    shell->input = NULL;
	shell->tokens = NULL;
}

/*
	Initializes signal handlers for the shell. 
	Handles SIGINT (Ctrl-C) for interactive mode.
	Ignores SIGQUIT (Ctrl-\) in the main shell process.
*/

void	set_signals(void)
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, SIG_IGN);
}

/*
	Signal handler. 
	Clears the current input line and redisplays the 
		prompt without exiting the shell.
*/

void	sighandler(int signal)
{
	
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
