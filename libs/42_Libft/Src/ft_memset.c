/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:55:41 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/09 09:57:44 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///ft_memset: Sets the first n bytes of the memory area point to by s to c;
///void *s: Pointer to the memory area;
///int c: Char to be set;
///size_t n: Number of bytes to be set;
///RETURN: SUCCESS: s

void	*ft_memset(void *s, int c, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (s);
}
/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	char cases[][32] = {
		"Hello World!",
		"abcdef",
		"1234567890",
		"with\0nulls",     // test with embedded null
		"short",
		"",
	};

	int chars[] = {
		'X',
		'Z',
		'0',
		'@',
		'A',
		'#'
	};

	size_t sizes[] = {
		5,   // partial overwrite
		6,   // full string
		10,  // numbers
		9,   // includes null
		3,   // partial
		0    // nothing to overwrite
	};

	int count = sizeof(sizes) / sizeof(sizes[0]);
	int i = 0;

	while (i < count)
	{
		char std_buf[32];
		char ft_buf[32];

		strcpy(std_buf, cases[i]);
		strcpy(ft_buf, cases[i]);

		memset(std_buf, chars[i], sizes[i]);
		ft_memset(ft_buf, chars[i], sizes[i]);

		printf("  memset result   : \"%s\"\n", std_buf);
		printf("  ft_memset result: \"%s\"\n", ft_buf);

		if (memcmp(std_buf, ft_buf, sizes[i]) == 0)
			printf("MATCH\n");
		else
			printf("MISMATCH\n");

		printf("--------------------------\n");
		i++;
	}
	return 0;
}*/
