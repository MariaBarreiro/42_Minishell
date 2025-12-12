#include "tokenizer_minishell.h"
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

int main(int ac, char **av, char  **env)
{
	t_shell	*shell;

    if (ac != 1 || av[1])
        return (ft_putstr_fd("[Error] Usage: ./minishell\n", 2),127);
    (void)ac;
    (void)av;
    shell = NULL;
	shell = init_shell(shell, env);
	global_sh = shell;
	set_signals();
	main_loop(shell, env);
}

t_shell	*init_shell(t_shell *shell, char **env)
{
	shell = malloc(sizeof(t_shell));
    shell->args = NULL;
	shell->exit_status = 0;
	shell->env = cpy_env(env);
	return (shell);
}
 
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



/*
	Fragment extractor.
*/

char	*get_single_token(t_shell *shell, const char *line, int *i)
{
	int		start_word;
	char	quote_type;
	char	*fragment;

	quote_type = 0;
	if (line[*i] == '\'' || line[*i] == '"')
	{
		quote_type = line[*i];
		(*i) += 1;
		start_word = *i;
		while (line[*i] && line[*i] != quote_type)
			(*i)++;
		if (line[*i] != quote_type)
			return (NULL);
		fragment = ft_substr(line, start_word, (*i - start_word));
		(*i) += 1;
	}
	else
	{
		start_word = *i;
		while (line[*i] && check_delimiter(line[*i]) == false && line[*i] != '"'
				&& line[*i] != ' ' && line[*i] != '\t' && line[*i] != '\'')
			(*i)++;
		fragment = ft_substr(line, start_word, (*i - start_word));
	}
	fragment = variable_expansion(shell, fragment, quote_type);
	return (fragment);
}

t_command_block	*parse_blocks(t_token *token, t_shell *shell)
{
	int				total_ac;
	t_command_block	*block[3];

	block[0] = NULL;
	block[1] = NULL;

	while (token)
	{
		total_ac  = count_ac(token);
		block[2] = new_block(total_ac);
		if (!block[2])
			return (NULL);
		if (fill_block(block[2], &token, shell, block[0]) != true)
			return (NULL);
		if (!block[0])
			block[0] = block[2];
		else
			block[1]->next = block[2];
		block[1] = block[2];
		if (token && token->type == T_PIPE)
		{
			token = token->next;
			if (!token || token->type == T_PIPE)
				return (pipe_error(block[0], shell), NULL);
		}
	}
	return (block[0]);
}

/*
	Determine how many command-line arguments exist before the next pipe symbol.
*/
int	count_ac(t_token *temp_token)
{
	int	counter;

	counter = 0;
	while (temp_token && temp_token->type != T_PIPE)
	{
		if (temp_token->type == T_WORD)
			counter += 1;
		temp_token = temp_token->next;
	}
	return (counter);
}

/*
	Allocate and initialize the new t_command_block structure to represent one command
		in the pipeline, complete with arrays for its arguments and redirections.
*/

t_command_block *new_block(int ac)
{
	t_command_block	*new_block;

	new_block = ft_calloc(1, sizeof(t_command_block));
	if (!new_block)
		return NULL;

	new_block->args = ft_calloc((ac + 1), sizeof(char *));
	new_block->limits = ft_calloc((ac + 1), sizeof(char *));
	new_block->input = ft_calloc((ac + 1), sizeof(char *));
	new_block->output = ft_calloc((ac + 1), sizeof(char *));

	return (new_block);
}

/*
	Consume tokens up to the next pipe and populate a single t_command_block.	
*/
bool	fill_block(t_command_block *block, t_token **token, t_shell *shell, t_command_block *head)
{
	int	i;

	i = 0;
	while (*token && (*token)->type != T_PIPE)
	{
		if ((*token)->type == T_WORD)
			block->args[i++] = ft_strdup((*token)->value);
		else if ((*token)->type == T_REDIR_IN || (*token)->type == T_REDIR_OUT 
					|| (*token)->type == T_REDIR_APPEND)
		{
			if (handle_redir(block, token, (*token)->type) == false)
				return (redir_error(head, block, shell, *token), false);
		}
		else if ((*token)->type == T_HEREDOC)
		{
			if (handle_heredoc(block, token) == false)
				return (redir_error(head, block, shell, *token), false);
		}
	(*token) = (*token)->next;
	}
	block->args[i] = NULL;
	return (true);
}

/*
	Validate and record an input or output for the current command block.
*/

bool	handle_redir(t_command_block *block, t_token **token, int type)
{
	char	*filename;
	int		index;

	filename = NULL;
	index = 0;
	(*token) = (*token)->next;
	if (!(*token) || (*token)->type == T_PIPE || (*token)->type == T_REDIR_IN
			|| (*token)->type == T_REDIR_OUT || (*token)->type == T_REDIR_APPEND
			|| (*token)->type == T_HEREDOC)
		return (false);
	if ((*token)->type == T_REDIR_IN)
	{
		filename = ft_strdup((*token)->value);
		index = block->redir_in;
		block->input[index] = filename;
		block->redir_in += 1;
	}
	else
	{
		if (type == T_REDIR_APPEND)
			block->redir_append += 1;
		filename = ft_strdup((*token)->value);
		index = block->redir_out;
		block->input[index] = filename;
		block->redir_out += 1;
	}
	return (true);
}

bool	redir_error(t_command_block *head, t_command_block *block, t_shell *shell, t_token *token)
{
	write(2, "bash: syntax error near unexpected token ", 41);
	if (!token)
		ft_putendl_fd("`newline'", 2);
	else if (token->type == T_REDIR_IN)
			ft_putendl_fd("`<'", 2);
	else if (token->type == T_REDIR_OUT)
			ft_putendl_fd("`>'", 2);
	else if (token->type == T_PIPE)
			ft_putendl_fd("`|'", 2);
	else if (token->type == T_REDIR_APPEND)
			ft_putendl_fd("`>>'", 2);
	else if (token->type == T_HEREDOC)
			ft_putendl_fd("`<<'", 2);
	free_blocks(head);
	free_blocks(block);
	shell->exit_status = 2;
	return (false);
}

/*
	Free an entire linked list of t_command_block, 
		including all the dynamically allocated arrays inside each block.	
*/

void	free_blocks(t_command_block	*head)
{
	if (!head)
		return ;
	t_command_block *temp;

	while (head)
	{
		temp = head->next;
		if (head->args)
			free_arrays(head->args);
		if (head->limits)
			free_arrays(head->limits);
		if (head->input)
			free_arrays(head->input);
		if (head->output)
			free_arrays(head->output);
		free(head);
		head = temp;
	}
}

/*
	Free all the arrays.
*/

void	free_arrays(char **array)
{
	int	i;
	i = 0;

	if (!array)
		return ;

	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/*
	Consume the << token.
	Validate the next token as a valid heredoc delimiter.
*/

bool	handle_heredoc(t_command_block *block, t_token **token)
{
	(*token) = (*token)->next;
	if (!(*token) || (*token)->type == T_PIPE || (*token)->type == T_REDIR_IN
			|| (*token)->type == T_REDIR_OUT || (*token)->type == T_REDIR_APPEND
			||(*token)->type == T_HEREDOC)
		return (false);
	block->limits[block->heredoc++] = ft_strdup((*token)->value);
	return (true);
}

/*
	Handle pipe syntax errors like | ls, ls | ls || wc.
		It cleans up any already-allocated blocks.
		Prints a bash-style error message.
		Sets the shell's exit status to indicate a syntax error
		Returns an error code for the parser to stop.
*/
static int	pipe_error(t_command_block *head, t_shell *shell)
{
	free_blocks(head);
	ft_putendl_fd("bash: syntax error near unexpected token `|'", 2);
	shell->exit_status = 1;
	return (-1);
}


