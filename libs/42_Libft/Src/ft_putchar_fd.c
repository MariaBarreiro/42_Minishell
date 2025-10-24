/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:29:49 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/15 18:35:00 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///ft_putchar_fd: Outputs the char 'c' to the specified file descriptor;
///char c: Char to output;
///int fd: File descriptor on which to write;

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}
/*
int	main()
{
	char c = 'c'; 
	int fd = 1;
	ft_putchar_fd(c, fd);
	return (0);
}*/
