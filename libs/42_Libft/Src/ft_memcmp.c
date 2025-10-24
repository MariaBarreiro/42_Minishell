/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:44:39 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/10 13:44:43 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///ft_memcmp: Compares the first n bytes of s1 and s2;
///const void *s1: Pointer to the first memory area;
///const void *s2: Pointer to the second memory area;
///size_t n: Maximum number of bytes to search for;
///RETURN: SUCCESS: Pointer to the first occurrence of c in s;
///RETURN: FAILURE: 0;

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p;
	unsigned char	*t;
	size_t			i;

	p = (unsigned char *)s1;
	t = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (p[i] != t[i])
			return (p[i] - t[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	const char *s1[] = {
		"abcdef",
		"abcdef",
		"abc\0def",
		"abc\0def",
		"abcdef",
		"abcXYZ",
		"abc",
		"abc",
		"",
		"same"
	};

	const char *s2[] = {
		"abcdeg",    // difference at last char
		"abcdef",    // identical
		"abc\0dxf",  // difference after null
		"abc\0def",  // identical with nulls
		"abcdee",    // difference at last char
		"abcXYZ",    // identical
		"abcd",      // different lengths
		"abc",       // identical
		"",          // empty
		"samb"       // diff at last char
	};

	size_t ns[] = {
		6, 6, 7, 7, 6, 6, 4, 3, 0, 4
	};

	int count = sizeof(ns) / sizeof(ns[0]);
	int i = 0;

	while (i < count)
	{
		int ft_res = ft_memcmp(s1[i], s2[i], ns[i]);
		int std_res = memcmp(s1[i], s2[i], ns[i]);

		printf("  ft_memcmp: %d\n", ft_res);
		printf("  memcmp   : %d\n", std_res);

		if ((ft_res == 0 && std_res == 0) 
		|| (ft_res < 0 && std_res < 0) || (ft_res > 0 && std_res > 0))
			printf("MATCH\n");
		else
			printf("MISMATCH\n");

		printf("--------------------------\n");
		i++;
	}

	return 0;
}*/
