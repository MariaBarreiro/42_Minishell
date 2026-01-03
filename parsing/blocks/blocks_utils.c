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
	Free an entire linked list of t_cmd_block, 
		including all the dynamically allocated arrays inside each block.	
*/

void	free_blocks(t_cmd_block	*head)
{
	if (!head)
		return ;
	t_cmd_block *temp;

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
