#include "../../../includes/minishell.h"

 int	count_unquoted_fields(char *value)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (value && value[i])
	{
		while (value[i] == ' ' || value[i] == '\t')
			i++;
		if (!value[i])
			break ;
		count++;
		while (value[i] && value[i] != ' ' && value[i] != '\t')
			i++;
	}
	return (count);
}
