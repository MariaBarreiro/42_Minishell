#include "tokenizer_minishell.h"

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
