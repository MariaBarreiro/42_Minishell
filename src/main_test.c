#include "./header.h"

int g_exit_status;

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

t_env	*init_env(char **envp)
{
	t_env	*head;
	int		i;
	char	*equal;

	head = NULL;
	i = 0;
	if (envp && envp[i])
	{
		head = malloc(sizeof(t_env));
		while (envp[i])
		{
			equal = ft_strchr(envp[i], '=');
			if (equal)
				env_add_back(&head, new_node
					(ft_substr(envp[i], 0, equal - envp[i]), ft_strdup(equal + 1)));
			else
				env_add_back(&head, new_node(ft_strdup(envp[i]), NULL));
			i++;
		}
	}
	return (head);
}

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
t_output	*populate_output()
{
	t_output	*head;
	//t_output	*second;

	head = malloc(sizeof(t_output));
	if (!head)
		return (NULL);
	head->file = ft_strdup("a.txt");
	head->append = 1;

/* 	second = malloc(sizeof(t_output));
	if (!second)
		return (NULL);
	second->file = ft_strdup("testando.txt");
	second->append = 1;
	second->next = NULL; */
	head->next = NULL;
	return (head);
}

t_cmd_block	*init_cmd_pwd(void)
{
	t_cmd_block	*cmd;

	cmd = malloc(sizeof(t_cmd_block));
	if (!cmd)
		return (NULL);
	cmd->redir_in = 0;
	//cmd->redir_out = 0;
	//cmd->redir_append = 0;
	cmd->heredoc = 0;
	cmd->heredoc_fd = -1;
	cmd->limits = NULL;
	cmd->input = NULL;
/* 	cmd->input = malloc(sizeof(char *) * 2);
	cmd->input[0] = ft_strdup("b.txt");
	cmd->input[1] = NULL; */
	//cmd->output = NULL;
	cmd->n_outputs = 1;
	cmd->outputs = populate_output();
	cmd->args = malloc(sizeof(char *) * 3);
	cmd->args[0] = ft_strdup("echo");
	cmd->args[1] = ft_strdup("MARCIO");
	cmd->args[2] = NULL;

	t_cmd_block	*second;

	second = malloc(sizeof(t_cmd_block));
	if (!second)
		return (NULL);
	second->redir_in = 0;
	//cmd->redir_out = 0;
	//cmd->redir_append = 0;
	second->heredoc = 0;
	second->heredoc_fd = -1;
	second->limits = NULL;
	second->input = NULL;
/* 	second->input = malloc(sizeof(char *) * 2);
	second->input[0] = ft_strdup("b.txt");
	second->input[1] = NULL; */
	//cmd->output = NULL;
	second->n_outputs = 0;
	second->outputs = NULL; //populate_output();
	second->args = malloc(sizeof(char *) * 3);
	second->args[0] = ft_strdup("cat");
	second->args[1] = ft_strdup("a.txt");
	second->args[2] = NULL;
	second->next = NULL;
	cmd->next = second;
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
	return (mini);
}


int	main(int ac, char **av, char **envp)
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
}
