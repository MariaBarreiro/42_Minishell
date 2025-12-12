#include "tokenizer_minishell.h"

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
