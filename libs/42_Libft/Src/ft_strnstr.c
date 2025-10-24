/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:17:47 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/18 10:55:39 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///ft_strnstr: Search for first occurence of a substring;
///const char *big: Pointer to the string to be searched;
///const char *little: Pointer to the string to search for;
///size_t len: Length of the string;
///RETURN: SUCCESS: Pointer to the substring;
///RETURN: FAILURE: Null;

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*little)
		return ((char *)big);
	while (big[i] && i < len)
	{
		while (big[i + j] && big[i + j] == little[j] && (i + j) < len)
		{
			j++;
			if (!little[j])
				return ((char *)(big + i));
		}
		i++;
		j = 0;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
#include <bsd/string.h>

int	main(void)
{
	// ---------- Test 1: basic match ----------
	const char *big1 = "Hello 42 Porto!";
	const char *lit1 = "42";
	char *ft1 = ft_strnstr(big1, lit1, 20);
	char *std1 = strnstr(big1, lit1, 20);
	printf("  ft_strnstr: %s\n", ft1);
	printf("  strnstr   : %s\n", std1);
	printf("----------------------------------\n");

	// ---------- Test 2: no match ----------
	const char *big2 = "Hello World!";
	const char *lit2 = "42";
	char *ft2 = ft_strnstr(big2, lit2, 12);
	char *std2 = strnstr(big2, lit2, 12);
	printf("  ft_strnstr: %s\n", ft2);
	printf("  strnstr   : %s\n", std2);
	printf("----------------------------------\n");

	// ---------- Test 3: match at end, len cuts it ----------
	const char *big3 = "Test here42";
	const char *lit3 = "42";
	char *ft3 = ft_strnstr(big3, lit3, 9);
	char *std3 = strnstr(big3, lit3, 9);
	printf("  ft_strnstr: %s\n", ft3);
	printf("  strnstr   : %s\n", std3);
	printf("----------------------------------\n");

	// ---------- Test 4: little is empty ----------
	const char *big4 = "Find me";
	const char *lit4 = "";
	char *ft4 = ft_strnstr(big4, lit4, 5);
	char *std4 = strnstr(big4, lit4, 5);
	printf("  ft_strnstr: %s\n", ft4);
	printf("  strnstr   : %s\n", std4);
	printf("----------------------------------\n");

	// ---------- Test 5: little longer than big ----------
	const char *big5 = "abc";
	const char *lit5 = "abcdef";
	char *ft5 = ft_strnstr(big5, lit5, 6);
	char *std5 = strnstr(big5, lit5, 6);
	printf("  ft_strnstr: %s\n", ft5);
	printf("  strnstr   : %s\n", std5);
	printf("----------------------------------\n");

	return 0;
}*/
