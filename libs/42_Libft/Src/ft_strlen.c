/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:39:12 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/18 10:30:04 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///ft_strlen: Take length of the string;
///const char *str: Pointer to the string;
///RETURN: SUCCESS: Length of the string;

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	// ---------- Test 1 ----------
	const char *str1 = "Porto";
	printf("  ft_strlen   : %lu\n", ft_strlen(str1));
	printf("  strlen      : %lu\n", strlen(str1));
	if (ft_strlen(str1) == strlen(str1))
		printf("MATCH\n");
	else
		printf("MISMATCH\n");
	printf("----------------------------------\n");

	// ---------- Test 2 ----------
	const char *str2 = "";
	printf("  ft_strlen   : %lu\n", ft_strlen(str2));
	printf("  strlen      : %lu\n", strlen(str2));
	if (ft_strlen(str2) == strlen(str2))
		printf("MATCH\n");
	else
		printf("MISMATCH\n");
	printf("----------------------------------\n");

	// ---------- Test 3 ----------
	const char *str3 = "   with spaces   ";
	printf("  ft_strlen   : %lu\n", ft_strlen(str3));
	printf("  strlen      : %lu\n", strlen(str3));
	if (ft_strlen(str3) == strlen(str3))
		printf("MATCH\n");
	else
		printf("MISMATCH\n");
	printf("----------------------------------\n");

	// ---------- Test 4 ----------
	const char *str4 = "specials!@#$%^&*()";
	printf("ft_strlen   : %lu\n", ft_strlen(str4));
	printf("strlen      : %lu\n", strlen(str4));
	if (ft_strlen(str4) == strlen(str4))
		printf("MATCH\n");
	else
		printf("MISMATCH\n");
	printf("----------------------------------\n");

	// ---------- Test 5 ----------
	const char *str5 = "This is a much longer string to test ft_strlen with.";
	printf("ft_strlen   : %lu\n", ft_strlen(str5));
	printf("strlen      : %lu\n", strlen(str5));
	if (ft_strlen(str5) == strlen(str5))
		printf("MATCH\n");
	else
		printf("MISMATCH\n");
	printf("----------------------------------\n");

	return 0;
}*/
