/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:16:37 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/18 10:51:20 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///ft_strncmp: Compares the first n bytes of s1 and s2;
///const char *s1: Pointer to the first string;
///const char *s2: Pointer to the second string;
///size_t n: Number of bytes to compare;
///RETURN: SUCCESS: 0;
///RETURN: FAILURE: Lexicographical difference;

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && (unsigned char)s1[i] == (unsigned char)s2[i])
	{
		if (s1[i] == '\0')
			return (0);
		i++;
	}
	if (i == n)
		return (0);
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}
/*
#include <stdio.h>
#include <string.h>


int	main(void)
{
	// ---------- Test 1: Equal strings ----------
	const char *s1 = "Hello";
	const char *s2 = "Hello";
	int ft1 = ft_strncmp(s1, s2, 5);
	int std1 = strncmp(s1, s2, 5);
	printf("ft_strncmp : %d\n", ft1);
	printf("strncmp    : %d\n", std1);
	printf("----------------------------------\n");

	// ---------- Test 2: Different strings ----------
	const char *s3 = "Hello";
	const char *s4 = "World";
	int ft2 = ft_strncmp(s3, s4, 3);
	int std2 = strncmp(s3, s4, 3);
	printf("ft_strncmp : %d\n", ft2);
	printf("strncmp    : %d\n", std2);
	printf("----------------------------------\n");

	// ---------- Test 3: Strings differ after n ----------
	const char *s5 = "HelloA";
	const char *s6 = "HelloZ";
	int ft3 = ft_strncmp(s5, s6, 5); // Should be equal
	int std3 = strncmp(s5, s6, 5);
	printf("ft_strncmp : %d\n", ft3);
	printf("strncmp    : %d\n", std3);
   printf("----------------------------------\n");

	// ---------- Test 4: One string is empty ----------
	const char *s7 = "";
	const char *s8 = "abc";
	int ft4 = ft_strncmp(s7, s8, 3);
	int std4 = strncmp(s7, s8, 3);
	printf("ft_strncmp : %d\n", ft4);
	printf("strncmp    : %d\n", std4);
	printf("----------------------------------\n");

	// ---------- Test 5: Both strings empty ----------
	const char *s9 = "";
	const char *s10 = "";
	int ft5 = ft_strncmp(s9, s10, 5);
	int std5 = strncmp(s9, s10, 5);
	printf("ft_strncmp : %d\n", ft5);
	printf("strncmp    : %d\n", std5);
	printf("----------------------------------\n");

	// ---------- Test 6: n = 0 ----------
	const char *s11 = "Hello";
	const char *s12 = "World";
	int ft6 = ft_strncmp(s11, s12, 0);
	int std6 = strncmp(s11, s12, 0);
	printf("ft_strncmp : %d\n", ft6);
	printf("strncmp    : %d\n", std6);
	printf("----------------------------------\n");

	// ---------- Test 7: Case sensitivity ----------
	const char *s13 = "abc";
	const char *s14 = "Abc";
	int ft7 = ft_strncmp(s13, s14, 3);
	int std7 = strncmp(s13, s14, 3);
	printf("ft_strncmp : %d\n", ft7);
	printf("strncmp    : %d\n", std7);
	printf("----------------------------------\n");

	return 0;
}*/
