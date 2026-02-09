#include "../../../includes/minishell.h"
/*
	Determine how many command-line arguments exist before the next pipe symbol.
*/

int	count_ac(t_token *temp_token)
{
	int	counter;

	counter = 0;
	while (temp_token && temp_token->type != T_PIPE)
	{
		if (temp_token->type == T_WORD && temp_token->value[0] != '\0')
			counter += 1;
		temp_token = temp_token->next;
	}
	return (counter);
}

/*
	Free an entire linked list of t_cmd_block, 
		including all the dynamically allocated arrays inside each block.	
*/

void	free_blocks(t_cmd_block	*head)
{
	t_cmd_block	*temp;

	while (head)
	{
		temp = head->next;
		free_block_arrays(head);
		free_output_list(head->outputs);
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

void	free_output_list(t_output *output)
{
	t_output	*next;

	while (output)
	{
		next = output->next;
		free(output->file);
		free(output);
		output = next;
	}
}

void	free_block_arrays(t_cmd_block *block)
{
	if (block->args)
		free_arrays(block->args);
	if (block->limits)
		free_arrays(block->limits);
	if (block->input)
		free_arrays(block->input);
}
