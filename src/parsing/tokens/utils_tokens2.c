#include "../../../includes/minishell.h"

char	*join_fragment(char *word, char *fragment)
{
	char	*temp;

	temp = word;
	if (word)
		word = ft_strjoin(word, fragment);
	else
		word = ft_strdup(fragment);
	free(temp);
	return (word);
}

char	*expand_fragment(t_mini *mini, char *fragment, char quote_type,
		int expand)
{
	if (!expand)
		return (fragment);
	fragment = tilde_fragment(mini, fragment, quote_type);
	return (var_expansion(mini, fragment, quote_type));
}

char	*expand_fragment(t_mini *mini, char *fragment, char quote_type,
		int expand)
{
	if (!expand)
		return (fragment);
	fragment = tilde_fragment(mini, fragment, quote_type);
	return (var_expansion(mini, fragment, quote_type));
}
