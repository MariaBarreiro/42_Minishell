/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlima-si <mlima-si@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:21:54 by mda-enca          #+#    #+#             */
/*   Updated: 2026/03/15 13:30:45 by mlima-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_last_limiter(char **limits)
{
	int	i;

	i = 0;
	while (limits[i + 1])
		i++;
	return (i);
}

char	*expand_variables(char *line, t_env *env)
{
	char	*res;
	char	*tmp;
	char	*val;
	int		i;

	res = ft_strdup("");
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			val = get_env_value(&line[i], env);
			if (val)
				res = ft_strjoin_free(res, val);
			while (line[i] && ft_isalnum(line[i]))
				i++;
		}
		else
			res = append_char(res, line[i++]);
	}
	tmp = res;
	return (tmp);
}

static void	write_heredoc(int fd, char *limit, t_env *env)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, limit))
		{
			free(line);
			break ;
		}
		expanded = expand_variables(line, env);
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(line);
		free(expanded);
	}
}

int	handle_heredocs(t_cmd_block *cmd, t_env *env)
{
	int	fd[2];
	int	i;

	if (!cmd->limits)
		return (1);
	i = get_last_limiter(cmd->limits);
	if (pipe(fd) < 0)
		exit(1);
	write_heredoc(fd[1], cmd->limits[i], env);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (0);
}
