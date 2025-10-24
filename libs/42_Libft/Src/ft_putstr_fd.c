/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:36:21 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/15 19:00:22 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///ft_putstr_fd: Outputs the str 's' to the specified file descriptor;
//char *s: String to output;
//int fd: File descriptor on which to write;

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (fd < 0)
		return ;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
}
/*
int	main()
{
	char s[] = "42Porto";
	int	fd = 1;
	ft_putstr_fd(s, fd);
	return(0);
}*/
