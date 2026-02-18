/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:21:51 by mda-enca          #+#    #+#             */
/*   Updated: 2026/02/18 17:21:52 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	save_fds(t_fd_backup *b)
{
	b->stdin_fd = dup(STDIN_FILENO);
	b->stdout_fd = dup(STDOUT_FILENO);
}

void	restore_fds(t_fd_backup *b)
{
	dup2(b->stdin_fd, STDIN_FILENO);
	dup2(b->stdout_fd, STDOUT_FILENO);
	close(b->stdin_fd);
	close(b->stdout_fd);
}

t_pipe	*create_pipes(int n)
{
	t_pipe	*p;
	int		i;

	p = malloc(sizeof(t_pipe) * (n - 1));
	if (!p)
		exit(1);
	i = 0;
	while (i < n - 1)
	{
		if (pipe(p[i]) == -1)
			exit(1);
		i++;
	}
	return (p);
}
