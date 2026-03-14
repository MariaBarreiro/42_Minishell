/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlima-si <mlima-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:21:48 by mda-enca          #+#    #+#             */
/*   Updated: 2026/03/14 16:39:10 by mlima-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (apply_redirections(mini->cmd, mini->my_env))
			exit(1);
		if (!mini->cmd->args || !mini->cmd->args[0])
			free_and_exit(mini, 0);
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

static int	exec_single_builtin(t_mini *mini, t_cmd_block *cmd)
{
	t_fd_backup	b;
	int			ret;

	save_fds(&b);
	if (apply_redirections(cmd, mini->my_env))
	{
		restore_fds(&b);
		mini->exit_stts = 1;
		return (1);
	}
	ret = exec_builtin(cmd->args, mini);
	restore_fds(&b);
	mini->exit_stts = ret;
	return (ret);
}

int	execute_pipeline(t_mini *mini)
{
	t_cmd_block	*cmd;
	int			ret;

	cmd = mini->cmd;
	if (cmd->next)
		return (execute_multiple(mini));
	if (is_builtin(cmd->args))
		return (exec_single_builtin(mini, cmd));
	ret = execute_external(mini);
	mini->exit_stts = ret;
	return (ret);
}
