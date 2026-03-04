/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_multiple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlima-si <mlima-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:21:37 by mda-enca          #+#    #+#             */
/*   Updated: 2026/03/04 12:37:29 by mlima-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	setup_child_pipes(int i, int total, t_pipe *p)
{
	int	j;

	j = 0;
	if (i > 0)
		dup2(p[i - 1][0], STDIN_FILENO);
	if (i < total - 1)
		dup2(p[i][1], STDOUT_FILENO);
	while (j < total - 1)
	{
		close(p[j][0]);
		close(p[j][1]);
		j++;
	}
}

static void	child_process(t_mini *mini, t_cmd_block *cmd,
			t_pipe *p, int i)
{
	int	n_cmds;

	n_cmds = count_cmds(mini->cmd);
	setup_child_pipes(i, n_cmds, p);
	if (apply_redirections(cmd))
		exit (1);
	if (is_builtin(cmd->args))
		exit(exec_builtin(cmd->args, mini));
	if (!cmd->args || !cmd->args[0])
		exit(0);
	execute_cmd(cmd, mini->my_env);
	exit(1);
}

static pid_t	*init_exec_multiple(t_pipe **pipes, int n_cmds)
{
	pid_t	*pids;

	*pipes = create_pipes(n_cmds);
	pids = malloc(sizeof(pid_t) * n_cmds);
	if (!*pipes || !pids)
		exit(1);
	return (pids);
}

static void	fork_loop(t_mini *mini, t_cmd_block *cmd,
			t_pipe *pipes, pid_t *pids)
{
	int	i;

	i = 0;
	while (cmd)
	{
		pids[i] = fork();
		if (pids[i] == 0)
			child_process(mini, cmd, pipes, i);
		cmd = cmd->next;
		i++;
	}
}

int	execute_multiple(t_mini *mini)
{
	t_cmd_block	*cmd;
	t_pipe		*pipes;
	pid_t		*pids;
	int			n_cmds;

	cmd = mini->cmd;
	n_cmds = count_cmds(cmd);
	pids = init_exec_multiple(&pipes, n_cmds);
	fork_loop(mini, cmd, pipes, pids);
	close_all_pipes(pipes, n_cmds);
	wait_all_children(pids, n_cmds, mini);
	free(pipes);
	free(pids);
	return (mini->exit_stts);
}
