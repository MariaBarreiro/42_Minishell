/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:21:18 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/10 12:21:20 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///ft_memchr: Locates the first occurrence of c in the s;
///const void *s: PLace in memory to search;
///int c: Char to search for;
///size_t n: Maximum number of bytes to search;
///RETURN: SUCCESS: Pointer to the first occurrence of c in s;
///REUTRN: FAILURE: Null;

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (p[i] == (unsigned char)c)
			return (p + i);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	const char *strings[] = {
		"42Porto!",         // Normal string
		"42Porto!",         // Char not found
		"42Porto!",         // Char at start
		"42Porto!",         // Char at end
		"42Porto!",         // Length 0
		"abc\0def",         // Look for '\0'
		"abc\0def",         // Look for 'd' before '\0'
		"",                 // Empty string
		"banana"            // Multiple matches for 'a'
	};

	int chars[] = {
		'P',                // Found in middle
		'X',                // Not found
		'4',                // At start
		'!',                // At end
		'P',                // Length = 0
		'\0',               // Null byte
		'd',                // After null byte (should not find)
		'a',                // Search in empty string
		'a'                 // Multiple matches
	};

	size_t ns[] = {
		8,                  // Full length
		8,
		8,
		8,
		0,                  // Should return NULL
		7,                  // Includes \0
		4,                  // Doesn't reach 'd'
		0,                  // Empty string, n = 0
		6                   // Whole string
	};

	int count = sizeof(chars) / sizeof(chars[0]);
	int i = 0;

	while (i < count)
	{
		const char *s = strings[i];
		int c = chars[i];
		size_t n = ns[i];

		void *ft_result = ft_memchr(s, c, n);
		void *std_result = memchr(s, c, n);

		if (ft_result != NULL)
			printf("  ft_memchr: \"%s\"\n", (char *)ft_result);
		else
			printf("  ft_memchr: NULL\n");

		if (std_result != NULL)
			printf("  memchr   : \"%s\"\n", (char *)std_result);
		else
			printf("  memchr   : NULL\n");

		if (ft_result == std_result)
			printf("MATCH\n");
		else
			printf("MISMATCH\n");

		printf("--------------------------\n");
		i++;
	}
	return 0;
}*/
