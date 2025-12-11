#include "built.h"

int g_exit_status;

static char	*build_prompt(char *cwd)
{
	int		len;
	char	*prompt;
	int		i = 0;

	len = ft_strlen(cwd) + 3;
	prompt = malloc(len + 1);
	if (!prompt)
		return (NULL);
	while (cwd[i])
	{
		prompt[i] = cwd[i];
		i++;
	}
	prompt[i++] = ' ';
	prompt[i++] = '>';
	prompt[i++] = ' ';
	prompt[i] = '\0';
	return (prompt);
}

int	main(int ac, char **av, char **envp)
{
	t_env *my_env = init_env(envp);

	g_exit_status = 0;
	(void)ac;
	(void)av;
	if (ac != 1 || av[1])
		return (ft_putstr_fd("[Error] Usage: ./minishell\n", 2),127);
	main_loop(&my_env);
	return (g_exit_status);
}

void	main_loop(t_env **my_env)
{
	char	*input;
	char	*prompt;
	char	*pwd;

	signal(SIGINT, ctrl_c);
	//signal(SIGQUIT, SIG_IGN);

	while (1)
	{
		pwd = get_env_value("PWD", *my_env);
		prompt = build_prompt(pwd);
		input = readline(prompt);
		free(prompt);
		if (!input)
		{
			ft_putstr_fd(("exit\n"), 2);
			break ;
		}
		else
			g_exit_status = exec_builtin(my_env, input);
		add_history(input);
		free(input);
	}
}
