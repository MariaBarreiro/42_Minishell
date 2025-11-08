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
	(void)ac;
	(void)av;
	if (ac != 1 || av[1])
		return (ft_putstr_fd("[Error] Usage: ./minishell\n", 2),127);
	main_loop();
}

void	main_loop(void)
{
	char *input;

	char buffer[1024];

	while (1)
	{
		printf("%s", getcwd(buffer, sizeof(buffer)));
		input = readline("> ");
		if (!input)
		{
			ft_putstr_fd(("exit"), 2);
			break ;
		}
		else
			builtin_command(input);
		add_history(input);
	}
}
