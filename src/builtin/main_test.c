#include "built.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (fd < 0)
		return ;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env *my_env = init_env(envp);

	(void)ac;
	(void)av;
	if (ac != 1 || av[1])
		return (ft_putstr_fd("[Error] Usage: ./minishell\n", 2),127);
	main_loop(&my_env);
}

void	main_loop(t_env **my_env)
{
	char *input;
	char buffer[1024];
	
	signal(SIGINT, ctrl_c);
	while (1)
	{
		printf("%s", getcwd(buffer, sizeof(buffer)));
		input = readline("> ");
		if (!input)
		{
			ft_putstr_fd(("exit\n"), 2);
			break ;
		}
		else
			builtin_command(my_env, input);
		add_history(input);
		free(input);
	}
}
