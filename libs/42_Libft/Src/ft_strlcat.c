/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 09:35:09 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/18 09:30:34 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///ft_strlcat: Appends size bytes from src to the dest;
///char *dst: Pointer to the destination str;
///const char *src: Pointer to the source str;
///size_t size: Number of byter to append;
///RETURN: SUCCESS: Number of bytes written;

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = ft_strlen(dst);
	k = ft_strlen(src);
	if (size == 0)
		return (k);
	if (size <= j)
		return (size + k);
	while (src[i] && (j + i) < (size - 1))
	{
		dst[j + i] = src[i];
		i++;
	}
	dst[j + i] = '\0';
	return (j + k);
}
/*
#include <stdio.h>
#include <bsd/string.h>

int	main(void)
{
	char dst1[20];
	char dst2[20];
	const char *src = "42Porto";

	// Test 1: Enough space
	strcpy(dst1, "Hello ");
	strcpy(dst2, "Hello ");
	printf("  ft_strlcat: %zu\n", ft_strlcat(dst1, src, sizeof(dst1)));
	printf("  Result: \"%s\"\n", dst1);
	printf("  strlcat   : %zu\n", strlcat(dst2, src, sizeof(dst2)));
	printf("  Result: \"%s\"\n", dst2);
	printf("----------------------------------\n");

	// Test 2: Truncation
	strcpy(dst1, "Hello ");
	strcpy(dst2, "Hello ");
	printf("  ft_strlcat: %zu\n", ft_strlcat(dst1, src, 10));
	printf("  Result: \"%s\"\n", dst1);
	printf("  strlcat   : %zu\n", strlcat(dst2, src, 10));
	printf("  Result: \"%s\"\n", dst2);
	printf("----------------------------------\n");

	// Test 3: size = 0
	strcpy(dst1, "Start");
	strcpy(dst2, "Start");
	printf("  ft_strlcat: %zu\n", ft_strlcat(dst1, src, 0));
	printf("  strlcat   : %zu\n", strlcat(dst2, src, 0));
	printf("----------------------------------\n");

	// Test 4: size smaller than dst length
	strcpy(dst1, "LongPrefix");
	strcpy(dst2, "LongPrefix");
	printf("  ft_strlcat: %zu\n", ft_strlcat(dst1, src, 5));
	printf("  strlcat   : %zu\n", strlcat(dst2, src, 5));
	printf("----------------------------------\n");

	return 0;
}*/
