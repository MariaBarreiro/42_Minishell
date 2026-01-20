//#include "../../../includes/minishell.h"
#include "../includes/minishell.h"
/* static int	has_value(char **venv)
{
	int	i, j;

	i = 0;
	while(venv[i])
	{
		j = 0;
		while(venv[i][j] != '=' && venv[i][j])
			j++;
		if (venv[i][j] == '=')
			return (1);
		i++;
	}
	return (0);
} */
/* 
t_mini	*init_minishell(t_cmd_block *cmd, char **envp)
{
	t_mini	*mini;
	
	mini = malloc(sizeof(t_mini));
	if (!mini)
	return (NULL);
	mini->exit_stts = 0;
	mini->cmd = cmd;
	mini->my_env = init_env(envp);
	if (init_minimal_env(&mini->my_env)) // <<<<<<<<<<<<<<<<<<iniciar SHSLVL
	exit(1);
	return (mini);
}

int	main(int ac, char **av, char **envp)
{
	t_mini		mini;
	t_cmd_block	*cmd1;
	t_cmd_block	*cmd2;
	
	(void)av;
	if (ac != 1)
	return (1);
	cmd1 = fake_cmd_echo_redir();
	cmd2 = fake_cmd_echo();
	cmd1->next = cmd2;
	mini.cmd = cmd1;
	mini.my_env = init_env(envp);
	mini.exit_stts = 0;
	execute_pipeline(&mini);
	return (0);
} */
/* 

char			*read_input_line(t_env **env);

/* static char	*build_prompt(char *cwd)
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
} */

/* int	main(int ac, char **av, char **envp)
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

char	*read_input_line(t_env **env)
{
	char	*prompt;
	char	*pwd;

	if (check_interactive() == 1)
	{
		pwd = get_env_value("PWD", *env);
		prompt = build_prompt(pwd);
		return (readline(prompt));
	}
	return (get_next_line(STDIN_FILENO));
}

void	main_loop(t_mini *mini)
{
	char		*input_line;
	int			ret;

	while (1)
	{
		input_line = read_input_line(&mini->my_env);
		if (!input_line)
		{
			if (check_interactive() == 1)
				ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (*input_line)
			add_history(input_line);
		mini->cmd = tokenizer(mini, input_line);
		ret = execute_pipeline(mini);
		if (mini->cmd)	
			free_blocks(mini->cmd);
		free(input_line);
		mini->exit_stts = ret;
	}
}
	*/