/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 08:05:20 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/18 09:39:08 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///ft_strlcpy: Copies size bytes from src to dest str;
///char *dst: Pointer to the destination string;
///const char *src: Pointer to the source string;
///size_t size: Maximum number of bytes to be copied;
///RETURN: SUCCESS: Number of bytes copied;

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (i < (size - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (i < size)
		dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}
/*
#include <stdio.h>
#include <bsd/string.h>

int	main(void)
{
	// ---------- Test 1 ----------
	const char *src1 = "Hello";
	size_t size1 = 0;
	char ft_dst1[30] = "XXXXXXXXX";
	char std_dst1[30] = "XXXXXXXXX";

	size_t ft_ret1 = ft_strlcpy(ft_dst1, src1, size1);
	size_t std_ret1 = strlcpy(std_dst1, src1, size1);

	printf("  ft_strlcpy: %zu | \"%s\"\n", ft_ret1, ft_dst1);
	printf("  strlcpy   : %zu | \"%s\"\n", std_ret1, std_dst1);
	if (ft_ret1 == std_ret1 && strcmp(ft_dst1, std_dst1) == 0)
		printf("MATCH\n");
	else
		printf("MISMATCH\n");
	printf("----------------------------------\n");

	// ---------- Test 2 ----------
	const char *src2 = "42School";
	size_t size2 = 3;
	char ft_dst2[30] = "XXXXXXXXX";
	char std_dst2[30] = "XXXXXXXXX";

	size_t ft_ret2 = ft_strlcpy(ft_dst2, src2, size2);
	size_t std_ret2 = strlcpy(std_dst2, src2, size2);

	printf("  ft_strlcpy: %zu | \"%s\"\n", ft_ret2, ft_dst2);
	printf("  strlcpy   : %zu | \"%s\"\n", std_ret2, std_dst2);
	if (ft_ret2 == std_ret2 && strcmp(ft_dst2, std_dst2) == 0)
		printf("MATCH\n");
	else
		printf("MISMATCH\n");
	printf("----------------------------------\n");

	// ---------- Test 3 ----------
	const char *src3 = "";
	size_t size3 = 6;
	char ft_dst3[30] = "XXXXXXXXX";
	char std_dst3[30] = "XXXXXXXXX";

	size_t ft_ret3 = ft_strlcpy(ft_dst3, src3, size3);
	size_t std_ret3 = strlcpy(std_dst3, src3, size3);

	printf("  ft_strlcpy: %zu | \"%s\"\n", ft_ret3, ft_dst3);
	printf("  strlcpy   : %zu | \"%s\"\n", std_ret3, std_dst3);
	if (ft_ret3 == std_ret3 && strcmp(ft_dst3, std_dst3) == 0)
		printf("MATCH\n");
	else
		printf("MISMATCH\n");
	printf("----------------------------------\n");

	// ---------- Test 4 ----------
	const char *src4 = "abcdef";
	size_t size4 = 10;
	char ft_dst4[30] = "XXXXXXXXX";
	char std_dst4[30] = "XXXXXXXXX";

	size_t ft_ret4 = ft_strlcpy(ft_dst4, src4, size4);
	size_t std_ret4 = strlcpy(std_dst4, src4, size4);

	printf("  ft_strlcpy: %zu | \"%s\"\n", ft_ret4, ft_dst4);
	printf("  strlcpy   : %zu | \"%s\"\n", std_ret4, std_dst4);
	if (ft_ret4 == std_ret4 && strcmp(ft_dst4, std_dst4) == 0)
		printf("MATCH\n");
	else
		printf("MISMATCH\n");
	printf("----------------------------------\n");

	// ---------- Test 5 ----------
	const char *src5 = "LongerThanBuffer";
	size_t size5 = 5;
	char ft_dst5[30] = "XXXXXXXXX";
	char std_dst5[30] = "XXXXXXXXX";

	size_t ft_ret5 = ft_strlcpy(ft_dst5, src5, size5);
	size_t std_ret5 = strlcpy(std_dst5, src5, size5);

	printf("  ft_strlcpy: %zu | \"%s\"\n", ft_ret5, ft_dst5);
	printf("  strlcpy   : %zu | \"%s\"\n", std_ret5, std_dst5);
	if (ft_ret5 == std_ret5 && strcmp(ft_dst5, std_dst5) == 0)
		printf("MATCH\n");
	else
		printf("MISMATCH\n");
	printf("----------------------------------\n");

	return 0;
}*/
