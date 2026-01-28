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


int	execute_pipeline(t_mini *mini)
{
	t_cmd_block *cmd;

	cmd = mini->cmd;
	if (cmd->next != NULL)
		return execute_multiple(mini);
	if (is_builtin(cmd->args))
	{
		if (!check_interactive())
		{
			pid_t pid = fork();
			if (pid == 0)
				exit(exec_builtin(cmd->args, mini));
			waitpid(pid, &mini->exit_stts, 0);
			mini->exit_stts = WEXITSTATUS(mini->exit_stts);
			return mini->exit_stts;
		}
		mini->exit_stts = exec_builtin(cmd->args, mini);
		return mini->exit_stts;
	}
	return execute_external(mini);
}
