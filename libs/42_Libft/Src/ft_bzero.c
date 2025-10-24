/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:12:55 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/09 11:14:26 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///ft_bzero: Sets the first n bytes of the memory area pointed to by s to 0;
///void *s: Memory area;
///size_t n: Number of bytes to be set to 0;

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
    ///two identical arrays/buffers with the same str
	char buffer1[16] = "Hello World!";
	char buffer2[16] = "Hello World!";
	size_t n = 5;

	ft_bzero(buffer1, n);
	bzero(buffer2, n);

    ///print in hexadeximal format to be able to the the null bytes
    printf("ft_bzero result: ");
	for (size_t i = 0; i < 12; i++)
		printf("%02x ", (unsigned char)buffer1[i]);
	printf("\n");

	printf("bzero    result: ");
	for (size_t i = 0; i < 12; i++)
		printf("%02x ", (unsigned char)buffer2[i]);
	printf("\n");

	if (memcmp(buffer1, buffer2, 12) == 0)
		printf("MATCH\n");
	else
		printf("MISMATCH\n");

	return 0;
}*/
