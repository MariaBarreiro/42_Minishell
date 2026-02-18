/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:21:59 by mda-enca          #+#    #+#             */
/*   Updated: 2026/02/18 17:22:18 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	handle_input(t_cmd_block *cmd)
{
	int	i;
	int	fd;

	if (!cmd->input)
		return (0);
	i = 0;
	while (cmd->input[i])
	{
		fd = open(cmd->input[i], O_RDONLY);
		if (fd < 0)
			return (perror(cmd->input[i]), 1);
		dup2(fd, STDIN_FILENO);
		close(fd);
		i++;
	}
	return (0);
}

static int	open_output_file(t_output *out)
{
	if (out->append)
		return (open(out->file, O_WRONLY | O_CREAT | O_APPEND, 0644));
	return (open(out->file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}

int	handle_output_redir(t_cmd_block *cmd)
{
	int			fd;
	t_output	*current;

	if (!cmd->outputs)
		return (0);
	current = cmd->outputs;
	while (current)
	{
		fd = open_output_file(current);
		if (fd < 0)
			return (perror(current->file), 1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		current = current->next;
	}
	return (0);
}

int	apply_redirections(t_cmd_block *cmd)
{
	if (cmd->last_redir == 1)
	{
		if (cmd->redir_in > 0)
			if (handle_input(cmd))
				return (1);
		if (cmd->heredoc > 0)
			handle_heredocs(cmd);
		if (cmd->n_outputs > 0)
			if (handle_output_redir(cmd))
				return (1);
	}
	else
	{
		if (cmd->heredoc > 0)
			handle_heredocs(cmd);
		if (cmd->n_outputs > 0)
			if (handle_output_redir(cmd))
				return (1);
		if (cmd->redir_in > 0)
			if (handle_input(cmd))
				return (1);
	}
	return (0);
}
