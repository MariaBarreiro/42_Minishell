#include "../parsing_header.h"

/*
	If it's delimiter create a token, else get the value.
		start is the head of the linked list.
*/

t_token	*init_token(t_mini *mini, t_token *head, char *line, int *i)
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
	else if (check_delimiter(line[*i]) == 1)
	{
		new->value = ft_substr(line, *i, 1);
		*i += 1;
	}
	else
		new->value = get_tokens(mini, line, i);
	if (!new->value)
	{
		free_tokens(head);
		free(new);
		return (NULL);
	}
	new->type = get_type(new->value);
	return (new);
}

/*
	Determine what kind of token a value represents.
*/

t_token_type get_type(char *value)
{
	if (redir_append_check(">>", value, ft_strlen(value)) == 1 && value[0])
		return (T_REDIR_APPEND);
	else if (heredoc_check("<<", value, ft_strlen(value)) == 1 && value[0])
		return (T_HEREDOC);
	else if (redir_in_check("<", value, ft_strlen(value)) == 1 && value[0])
		return (T_REDIR_IN);
	else if (redir_out_check(">", value, ft_strlen(value)) == 1 && value[0])
		return (T_REDIR_OUT);
	else if (pipe_check("|", value, ft_strlen(value)) == 1 && value[0])
		return (T_PIPE);
	else
		return (T_WORD);
}

/*
	Word constructor!
		Builds one word at a time!
*/

char	*get_tokens(t_mini *mini, const char *line, int *i)
{
	char	*word;
	char	*fragment;
	char	*temp;

	word = NULL;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\t' && check_delimiter(line[*i]) == 0)
	{
		fragment = get_single_token(mini, line, i);
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

char	*get_single_token(t_mini *mini, const char *line, int *i)
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
		while (line[*i] && check_delimiter(line[*i]) == 0 && line[*i] != '"'
				&& line[*i] != ' ' && line[*i] != '\t' && line[*i] != '\'')
			(*i)++;
		fragment = ft_substr(line, start_word, (*i - start_word));
	}
	fragment = variable_expansion(mini, fragment, quote_type);
	return (fragment);
}
