#include "../parsing_header.h"
#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

/*global struct holding the state of my shell.*/
t_shell	*global_sh;

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
        return (ft_putstr_fd("[Error] Usage: ./minishell\n", 2),127);
    (void)ac;
    (void)av;
	set_signals();
	init_minishell(&mini, envp);
	//
	//
	main_loop(shell, env);
}

void	init_minishell(t_mini *mini, char **envp)
{

	mini = malloc(sizeof(t_mini));
	if (!mini)
		return (NULL);
	mini->token = NULL;	
	mini->input = NULL;

}
/* 
t_env	*init_env(char **envp)
{
	t_env	*head;
	int		i;
	char	*equal;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (equal)
			env_add_back(&head, new_node
				(ft_substr(envp[i], 0, equal - envp[i]), ft_strdup(equal + 1)));
		else
			env_add_back(&head, new_node(ft_strdup(envp[i]), NULL));
		i++;
	}
	return (head);
}*/
/*
//
	Create a copy of env with allocation of memory.//

char	**cpy_env(char **env)
{
	size_t	i;

	i = 0;
	while(env[i])
		i++;
	char **new_env = (char **)malloc((i + 1) * sizeof(char *));
	if (!new_env)
		return NULL;
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}
*/
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
	(void)signal;
	if(global_sh)
		global_sh->exit_status = 130;
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

