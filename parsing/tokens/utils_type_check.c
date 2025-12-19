#include "tokenizer_minishell.h"

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
