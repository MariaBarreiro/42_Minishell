/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 07:55:40 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/18 10:59:50 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///ft_strrchr: Search for the last occurence of a char;
///const char *s: Pointer of the string to be searched;
///int c: Char to search for;
///RETURN: SUCCESS: Pointer to the last occurence of c;
///RETURN: FAILURE: Null;

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*p;

	i = 0;
	p = 0;
	while (s[i])
	{
		if ((unsigned char)s[i] == (char)c)
			p = ((char *)(s + i));
		i++;
	}
	if ((unsigned char)s[i] == (char) c)
		return ((char *)(s + i));
	return (p);
}
/*
#include <stdio.h>
#include <string.h>


int	main(void)
{
	const char *test_strings[] = {
		"42Porto!",
		"hello",
		"abcabcabc",
		"ends with !",
		"just testing",
		"test",
		""
	};

	int test_chars[] = {
		'o',    // Appears twice
		'z',    // Not in string
		'a',    // Multiple times
		'!',    // At end
		't',    // Appears once
		'\0',   // Null terminator
		'x'     // Not in string
	};

	int total_tests = sizeof(test_strings) / sizeof(test_strings[0]);
	int i = 0;

	while (i < total_tests)
	{
		const char *s = test_strings[i];
		int c = test_chars[i];

		char *ft = ft_strrchr(s, c);
		char *std = strrchr(s, c);

		printf("  ft_strrchr    : %s\n", ft ? ft : "NULL");
		printf("  strrchr       : %s\n", std ? std : "NULL");

		if (ft == std)
			printf("MATCH\n");
		else if (ft && std && strcmp(ft, std) == 0)
			printf("MATCH\n");
		else
			printf("MISMATCH\n");

		printf("----------------------------------\n");
		i++;
	}
	return 0;
}*/
