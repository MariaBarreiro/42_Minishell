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
		free(input_line);
	}
}

/*
	Determine if its a terminal or not.
*/

bool	check_interactive(void)
{
	if (isatty(STDIN_FILENO))
		return (true);
	return (false);
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
	char	*var_name;
	char	*var_value;
	char	*return_var;

	i = 1;
	start = ft_strchr(fragment, '$');
	if (!start[1])
		return (fragment);
	if (start[1] == '?')
		return (concat(start, fragment, ft_itoa(exit_status), (i + 1)));
	if (start[1] == '{')
		return(get_brace(env, fragment, start));
	while (start[i] && (ft_isalnum(start[i]) || start[i] == '_'))
		i++;
	var_name = ft_substr(start, 1, i - 1);
	var_value = get_env_value(env, var_name);
	free(var_name);
	return_var = concat(start, fragment, var_value, i);
	return (return_var);
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
	Handle ${VAR} expansions safely.
*/

char	*get_brace(char **env, char *fragment, char *start)
{
	char	*closing_brace;
	char	*var_name;
	char	*var_value;
	int		len;

	closing_brace = ft_strchr((start + 2), '}');
	if (!closing_brace)
	{
		free(fragment);
		return (ft_strdup(""));
	}
	len = closing_brace - (start + 2);
	if (len == 0)
	{
		free(fragment);
		return (ft_strdup(""));
	}
	var_name = ft_substr((start + 2), 0, len);
	var_value = get_env_value(env, var_name);
	free(var_name);
	return (concat(start, fragment, var_value, len + 3));
}

/*
	Find an environment variable's value by name.
*/

char	*get_env_value(char **env, char *var_name)
{
	int	i;
	int	var_len;

	i = 0;
	var_len = ft_strlen(var_name);
	while (env[i])
	{
	if (ft_strncmp(env[i], var_name, var_len) == 0 && env[i][var_len] == '=')
			return (ft_strdup(env[i] + var_len + 1));
		i++;
	}
	return (ft_strdup(""));
}

/*
	Get the type and update the current.
*/

void	new_token(t_token **new_token, t_token **head, t_token **current)
{
	(*new_token)->type = get_type((*new_token)->value);
	(*new_token)->next = NULL;

	if(!head)
	{
		*head = *new_token;
		*new_token = *current;
	}
	else
	{
		(*current)->next = *new_token;
		*current = *new_token;
	}
}

/*
	Determine what kind of token a value represents.
*/

t_token_type get_type(char *value)
{
	if (redir_out_token_check("<", value, ft_strlen(value)) == true && value[0])
		return (T_REDIR_OUT);
	else if (redir_append_token_check(">>", value, ft_strlen(value)) == true && value[0])
		return (T_REDIR_APPEND);
	else if (redir_in_token_check("<", value, ft_strlen(value)) == true && value[0])
		return (T_REDIR_IN);
	else if (pipe_token_check("|", value, ft_strlen(value)) == true && value[0])
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


