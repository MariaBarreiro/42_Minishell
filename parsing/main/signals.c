#include "../parsing_header.h"
int g_exit_status;

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
	g_exit_status = 128 + signal;
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

