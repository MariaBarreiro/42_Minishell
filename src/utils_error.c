/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 17:28:50 by mda-enca          #+#    #+#             */
/*   Updated: 2026/02/18 17:28:51 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	error(t_token *token, char *message, int exit_code)
{
	if (token)
		free_tokens(token);
	ft_putendl_fd(message, 2);
	exit (exit_code);
}
