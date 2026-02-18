/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:21:44 by mda-enca          #+#    #+#             */
/*   Updated: 2026/02/18 17:21:45 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_cmds(t_cmd_block *cmd)
{
	int			i;
	t_cmd_block	*temp;

	i = 0;
	temp = cmd;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

void	close_all_pipes(t_pipe *pipes, int n_cmds)
{
	int	i;

	i = 0;
	while (i < n_cmds - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	handle_status(int status, t_mini *mini)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			mini->exit_stts = 130;
		else if (sig == SIGQUIT)
			mini->exit_stts = 131;
		else
			mini->exit_stts = 128 + sig;
	}
	else if (WIFEXITED(status))
		mini->exit_stts = WEXITSTATUS(status);
	else
		mini->exit_stts = 1;
}

void	wait_all_children(pid_t *pids, int n, t_mini *mini)
{
	int	status;
	int	i;

	i = 0;
	while (i < n)
	{
		waitpid(pids[i], &status, 0);
		if (i == n - 1)
		{
			if (WIFEXITED(status))
				mini->exit_stts = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				mini->exit_stts = 128 + WTERMSIG(status);
		}
		i++;
	}
}

int	validate_cmd(char *cmd, char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		print_error(cmd, "Is a directory");
		return (0);
	}
	if (access(path, X_OK) != 0)
	{
		print_error(cmd, "Permission denied");
		return (0);
	}
	return (1);
}
