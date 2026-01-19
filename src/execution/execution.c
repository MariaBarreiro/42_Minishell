#include "../../includes/minishell.h"

static int	execute_external(t_mini *mini)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		setup_redirections(mini->cmd);
		execute_cmd(mini->cmd, mini->my_env);
		exit(1);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}


int execute_pipeline(t_mini *mini)
{
	t_cmd_block	*cmd;
	int			ret;

	cmd = mini->cmd;
	if (cmd->next != NULL)
		return (execute_multiple(mini));
	if (is_builtin(cmd->args))
	{
		ret = exec_builtin(cmd->args, mini);
		mini->exit_stts = ret;
		return (ret);
	}
	ret = execute_external(mini);
	mini->exit_stts = ret;
	return (ret);
}

