/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 07:12:32 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/16 07:12:37 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///ft_putendl_fd: Outputs the str 's' to the specified file descriptor
///				followed by a newline;
///char *s: String to output;
///int fd: File descriptor on which to write;

void	ft_putendl_fd(char *s, int fd)
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
	write (fd, "\n", 1);
}
/*
int	main()
{
	char s[] = "42Porto";
	int	fd = 1;
	ft_putendl_fd(s, fd);
	return (0);
}*/
