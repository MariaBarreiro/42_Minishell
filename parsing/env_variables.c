#include "tokenizer_minishell.h"

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
	fragment = var_expan(shell, fragment, quote_type);
	return (fragment);
}

/*
	Expand variables.
		Doesn't happen with single quotes!!
*/

char	*var_expan(t_shell *shell, char *fragment, char quote_type)
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

