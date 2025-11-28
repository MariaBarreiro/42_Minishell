#include "built.h"

static int	env_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static void	ft_swap(t_env **a, t_env **b)
{
	t_env	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void sort_env_array(t_env **arr, int size)
{
	int	i;
	int	j;

	for (i = 0; i < size - 1; i++)
	{
		for (j = 0; j < size - i - 1; j++)
		{
			if (ft_strcmp(arr[j]->name, arr[j + 1]->name) > 0)
				ft_swap(&arr[j], &arr[j + 1]);
		}
	}
}

static void print_export_line(t_env *env)
{
	if (!ft_strcmp(env->name, "_"))
		return ;
	printf("declare -x %s", env->name);
	if (env->value)
		printf("=\"%s\"", env->value);
	printf("\n");
}

int print_variables(t_env *my_env)
{
	int		size;
	int		i;
	t_env	**arr;
	t_env	*tmp;

	size = env_size(my_env);
	i = 0;
	tmp = my_env;
	if (size == 0)
		return (0);
	arr = malloc(sizeof(t_env *) * size);
	if (!arr)
		return (0);
	while (tmp)
	{
		arr[i++] = tmp;
		tmp = tmp->next;
	}
	sort_env_array(arr, size);
	for (i = 0; i < size; i++)
		if (arr[i]->exported == 1)
			print_export_line(arr[i]);
	free(arr);
	return (1);
}
