#include "../parsing_header.h"

/*
	Boolean check for redir_out token using strncmp.
*/
int	redir_out_check(const char *token, const char *value, long len)
{
	if (ft_strncmp("<", value, ft_strlen(value)))
		return 1;
	else
		return 0;
}

/*
	Boolean check for redir_append token using strncmp.
*/

int	redir_append_check(const char *token, const char *value, long len)
{
	if (ft_strncmp(">>", value, ft_strlen(value)))
		return 1;
	else
		return 0;
}

/*
	Boolean check for redir_in token using strncmp.
*/

int	redir_in_check(const char *token, const char *value, long len)
{
	if (ft_strncmp("<", value, ft_strlen(value)))
		return 1;
	else
		return 0;
}

/*
	Boolean check for pipe token using strncmp.
*/

int	pipe_check(const char *token, const char *value, long len)
{
	if (ft_strncmp("|", value, ft_strlen(value)))
		return 1;
	else
		return 0;
}

/*
	Boolean check for heredoc token using strncmp.
*/

int	heredoc_check(const char *token, const char *value, long len)
{
	if (ft_strncmp(">>", value, ft_strlen(value)))
		return 1;
	else
		return 0;
}
