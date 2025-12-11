#include "header.h"

int execute_multiple(t_command_block **cmd_list) //(2)
{
	t_command_block *cmd = *cmd_list;
	int num_cmd = count_commands(cmd);
	int pipes[num_cmd - 1][2];
	pid_t pids[num_cmd];
	for (int i = 0; i < num_cmd - 1; i++)
		pipe(pipes[i]);
	t_command_block *node = cmd;
	for (int i = 0; i < num_cmd; i++)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			handle_pipes(node, pipes, i, num_cmd);
			handle_redirs(node);
			execute_child(node);
		}
		node = node->next;
	}
	for (int i = 0; i < num_cmd - 1; i++)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
	for (int i = 0; i < num_cmd; i++)
		waitpid(pids[i], NULL, 0);

	return (0);
}

void execute_child(t_command_block *cmd)
{
	if (is_builtin(cmd->args))
		exit(execute_builtin_child(cmd)); // builtin no filho
	execve(resolve_path(cmd->args[0]), cmd->args, global_sh->env);
	perror("execve");
	exit(1);
}

int	execute_external(t_command_block *node);

int	count_commands(t_command_block *cmd) //(3)
{
	int	i;

	while(cmd)
	{
		cmd = cmd->next;
		i++;
	}
	return i;
}

void apply_redirections(t_command_block *cmd)
{
	// 1) input redirections
	// 2) output redirections
	// 3) heredoc (se existir)
}


int execute_pipeline(t_command_block **cmd) //(1)
{
	t_command_block	*node;

	node = *cmd;
	if (node->next)
		return (execute_multiple(cmd));
	if (is_builtin(node->args))
		return (exec_builtin(node->args, node));
	return (execute_external(node));
}
