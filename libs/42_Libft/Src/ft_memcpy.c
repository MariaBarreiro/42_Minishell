/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:49:29 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/09 13:20:13 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///ft_memcpy: Copies n bytes from memory area src to memory area dest;
///void *dest: POunter to the destination memory area;
///const void *src: POinter to the source memory area;
///size_t n: Number of bytes to be copied;
///RETURN: SUCCESS: Dest;
///RETURN: FAILURE: Null;

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	i = 0;
	if (!dest && !src)
		return (0);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	char cases[][32] = {
		"Hello, World!",
		"abcdef",
		"1234567890",
		"with\0nulls",
		"overlap test",   // but memcpy shouldn't handle overlaps!
		"short",
		"",
	};

	size_t sizes[] = {
		5,    // Copy part of string
		6,    // Copy full string
		10,   // Copy digits
		9,    // Includes null byte in middle
		7,    // Test with potential overlap
		3,    // Partial copy
		0     // Nothing to copy
	};

	int count = sizeof(sizes) / sizeof(sizes[0]);
	int i = 0;

	while (i < count)
	{
		char std_buf[32] = {0};
		char ft_buf[32] = {0};

		memcpy(std_buf, cases[i], sizes[i]);
		ft_memcpy(ft_buf, cases[i], sizes[i]);

		printf("  memcpy result   : \"%s\"\n", std_buf);
		printf("  ft_memcpy result: \"%s\"\n", ft_buf);

		if (memcmp(std_buf, ft_buf, sizes[i]) == 0)
			printf("MATCH\n");
		else
			printf("MISMATCH\n");

		printf("--------------------------\n");
		i++;
	}

	return 0;
}*/
