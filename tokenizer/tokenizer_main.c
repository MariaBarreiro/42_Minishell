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
	Create a copy of env with allocation of memory.
*/

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
	Main interactive loop for minishell.
	Handles the Read, Evaluate, Print Loop cycle for user interaction.
		Reads input.
		Process commands.
		Manages exit conditions.
*/

void    main_loop(t_shell *shell, char **env)
{
    char			*input;
	t_command_block	*blocks;

    while (1)
    {
        /*input = readline("minishell");
		if (!input)
		{
			ft_putstr_fd(("exit"), 2);
			break ;
		}
		add_history(input);*/
		blocks = tokenizer(shell, input);

    }
}

/*
	Fills token data with the input string.
		Line is the input from the user.
		Return the token created.
*/

t_command_block	*tokenizer(t_shell *shell, char *line)
{
	t_token			*token;
	t_command_block	*blocks;

	blocks = NULL;

	//Check if there's something there.
	if (!line[0] || !ft_strcmp(line, "$NOTHING") ||check_spaces(line) == false)
		return NULL;
	
	//Check for the $EMPTY marker and skip it.
	if (!ft_strncmp(line, "$NOTHING", 8))
		line += 6;
	
	//Check if line is "" (or "" followed by a space).
	if (!ft_strncmp(line, "\"\"", 2) && (!line[2] || line[2] == ' '))
	{
		ft_putendl_fd(":command not found", STDERR_FILENO);
		shell->exit_status = 127;
		return (NULL);
	}

	//Turn raw input into a token list.
	token = tokenization(shell, line);
	if (!token)
	{
		printf("Error: input incorrect\n");
		return NULL;
	}

	//Turn tokens into executable blocks.
	blocks = parse_blocks(token, shell);

	//Free the tokens and keep the parsed struct.
	free_tokens(token);
	return (blocks);
}

/*
	Ignore spaces and \t. If there's still str after that return true, 
		else return false.
*/

bool	check_spaces(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i])
		return (true);
	return (false);
}

/*
	Alloc memory and call functions for value and type.
*/

t_token	*tokenization(t_shell *shell, char *line)
{
	t_token	*head;				//Head to the linked list.
	t_token	*current;			//Current variable used to walk inside the list.
	t_token	*new;				//New node.
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			i++;
		else
		{
			new = init_token(shell, head, line, &i);
			if (!new)
				return (NULL);
			new_token(&new, &head, &current);
		}
	}
	return (head); 
}

/*
	If it's delimiter create a token, else get the value.
		start is the head of the linked list.
*/

t_token	*init_token(t_shell *shell, t_token *head, char *line, int *i)
{
	t_token	*new;

	new = calloc(sizeof(t_token), 1);
	if (!new)
		error(head, "Error: failed in memory allocate\n", 1);
	if (line[*i] == '>' && line[1 + *i] == '>' 
		|| line[*i] == '<' && line[1 + *i] == '<')
	{
		new->value = ft_substr(line, *i, 2);
		*i += 2;
	}
	else if (check_delimiter(line[*i]) == true)
	{
		new->value = ft_substr(line, *i, 1);
		*i += 1;
	}
	else
		new->value = get_tokens(shell, line, i);
	if (!new->value)
	{
		free_tokens(head);
		free(new);
		return (NULL);
	}
	return (new);
}

bool	check_delimiter(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (true);
	return (false);
}

/*
	Word constructor!
		Builds one word at a time!
*/

char	*get_tokens(t_shell *shell, const char *line, int *i)
{
	char	*word;
	char	*fragment;
	char	*temp;

	word = NULL;

	while (line[*i] && line[*i] != ' ' && line[*i] != '\t' && check_delimiter(line[*i]) == false)
	{
		fragment = get_single_token(shell, line, i);
		if (!fragment)
		{
			free(word);
			return (NULL);
		}
		temp = word;
		if (word)
			word = ft_strjoin(word, fragment);
		else
			word = ft_strdup(fragment);
		free(temp);
		free(fragment);
	}
	return (word);
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

/*
	Expand variables.
		Doesn't happen with single quotes!!
*/

char	*variable_expansion(t_shell *shell, char *fragment, char quote_type)
{
	char	*position;

	while(quote_type != '\'' && ft_strchr(fragment, '$'))
	{
		position = ft_strchr(fragment, '$');
		if (!position[1] || position[1] == ' ' || check_delimiter(position[1]) == true)
			break ;
		fragment = get_variable(shell->env, fragment, shell->exit_status);
	}
	return (fragment);
}

/*
    Replace the first $VARIABLE (or '$?', or ${VAR}) inside the fragment with its value 
        from env returning a new expanded string.
*/

char    *get_variable(char **env, char *fragment, int exit_status)
{
	int		i;
	char	*start;

	i = 1;
	start = ft_strchr(fragment, '$');
	if (!start[1])
		return (fragment);
	if (start[1] == '?')
		return (concat(start, fragment, ft_itoa(exit_status), (i + 1)));
}

/*
	Reconstruct the full string after expanding one variable.
*/

char	*concat(char *start, char *fragment, char *var_exit_value, int i)
{
	int		prefix_len;
	char	*prefix;
	char	*suffix;
	char	*temp_result;
	char	*result;

	prefix_len = start - fragment;
	prefix = ft_substr(fragment, 0, prefix_len);
	suffix = ft_strdup(start + i);
	temp_result = ft_strjoin(prefix, var_exit_value);
	result = ft_strjoin(temp_result, suffix);

	free(fragment);
	free(prefix);
	free(suffix);
	free(temp_result);
	free(var_exit_value);

	return(result);
}

/*
	Get the type and update the current.
*/

void	new_token(t_token **new, t_token **head, t_token **current)
{
	(*new)->type = get_type((*new)->value);
	(*new)->next = NULL;

	if(!head)
	{
		*head = *new;
		*new = *current;
	}
	else
	{
		(*current)->next = *new;
		*current = *new;
	}
}

/*
	Determine what kind of token a value represents.
*/

t_token_type get_type(char *value)
{
	if (redir_out_token_check("<", value, ft_strlen(value)) == true && value[0])
		return (T_REDIR_OUT);
	else if (redir_append_token_check(">>", value, ft_strlen(value)) == true) && value[0])
		return (T_REDIR_APPEND);
	else if (redir_in_token_check("<", value, ft_strlen(value)) == true) && value[0])
		return (T_REDIR_IN);
	else if (pipe_token_check("|", value, ft_strlen(value)) == true) && value[0])
		return (T_PIPE);
	else if (heredoc_token_check("<<", value, ft_strlen(value)) == true && value[0])
		return (T_HEREDOC);
	else
		return (T_WORD);
}

/*
	Boolean check for redir_out token using strncmp.
*/
bool	redir_out_token_check(const char *token, const char *value, size_t len_value)
{
	if (ft_strncmp("<", value, ft_strlen(value)))
		return true;
	else
		return false;
}

/*
	Boolean check for redir_append token using strncmp.
*/

bool	redir_append_token_check(const char *token, const char *value, size_t len_value)
{
	if (ft_strncmp(">>", value, ft_strlen(value)))
		return true;
	else
		return false;
}

/*
	Boolean check for redir_in token using strncmp.
*/

bool	redir_in_token_check(const char *token, const char *value, size_t len_value)
{
	if (ft_strncmp("<", value, ft_strlen(value)))
		return true;
	else
		return false;
}

/*
	Boolean check for pipe token using strncmp.
*/

bool	pipe_token_check(const char *token, const char *value, size_t len_value)
{
	if (ft_strncmp("|", value, ft_strlen(value)))
		return true;
	else
		return false;
}

/*
	Boolean check for heredoc token using strncmp.
*/

bool	heredoc_token_check(const char *token, const char *value, size_t len_value)
{
	if (ft_strncmp(">>", value, ft_strlen(value)))
		return true;
	else
		return false;
}

t_command_block	*parse_blocks(t_token *token, t_shell *shell)
{
	int		total_ac;
	t_block	*blocks[3];

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
				return (redir_error(), false);
		}
		else if ((*token)->type == T_HEREDOC)
		{
			if (handle_heredoc() == false)
				return (redir_error, false);
		}
	(*token) = (*token)->next;
	}
	block->args[i] = '\0';
	return (true);
}

/*
	Validate and record an input or output for the current command block.
*/

bool	handle_redir(t_command_block *block, t_token **token, int type)
{
	(*token) = (*token)->next;
	if (!(*token) || (*token)->type == T_PIPE || (*token)->type == T_REDIR_IN
			|| (*token)->type == T_REDIR_OUT || (*token)->type == T_REDIR_APPEND
			|| (*token)->type == T_HEREDOC)
		return (false);
	if ((*token)->type == T_REDIR_IN)
		block->input[]
}

/*
	
*/
static int	pipe_error(t_command_block *head, t_shell *shell)
{
}



