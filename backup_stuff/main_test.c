//#include "./header.h"
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
			g_exit_status = exec_line(my_env, input);
		add_history(input);
		free(input);
	}
} */
t_cmd_block	*fake_cmd_echo_redir(void)
{
	t_cmd_block	*cmd;
	t_output	*out;
	cmd = malloc(sizeof(t_cmd_block));
	cmd->args = malloc(sizeof(char *) * 3);
	cmd->args[0] = ft_strdup("echo");
	cmd->args[1] = ft_strdup("marcio");
	cmd->args[2] = NULL;

	out = malloc(sizeof(t_output));
	out->file = ft_strdup("a.txt");
	out->append = 1;
	out->next = NULL;

	cmd->outputs = out;
	cmd->n_outputs = 1;
	cmd->input = NULL;
	cmd->heredoc = 0;
	cmd->heredoc_fd = -1;
	cmd->limits = NULL;
	cmd->next = NULL;

	return (cmd);
}

t_cmd_block	*fake_cmd_echo(void)
{
	t_cmd_block	*cmd;
	cmd = malloc(sizeof(t_cmd_block));
	cmd->args = malloc(sizeof(char *) * 3);
	cmd->args[0] = ft_strdup("echo");
	cmd->args[1] = ft_strdup("abc");
	cmd->args[2] = NULL;
	cmd->outputs = NULL;
	cmd->n_outputs = 0;
	cmd->input = NULL;
	cmd->heredoc = 0;
	cmd->heredoc_fd = -1;
	cmd->limits = NULL;
	cmd->next = NULL;
	return (cmd);
}


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
}


/* int	main(int ac, char **av, char **envp)
{
	t_mini		*mini;
	t_cmd_block	*cmd;

	(void)av;
	if (ac != 1)
		return (1);
	cmd = init_cmd_pwd();
	mini = init_minishell(cmd, envp);
	execute_pipeline(mini);
	return (0);
} */
