/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 16:27:59 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/09 16:38:02 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///ft_strchr: Searches for the first occurrence of the char c;
///const char *s: String to be searched;
///int c: Char to search for;
///RETURN: SUCCESS: Pointer to he first occurrence of the char c in the str s;

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (0);
}
/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	const char *inputs[] = {
		"42Porto",
		"hello",
		"abcdef",
		"",
		"abcabcabc",
		"string\0test"
	};

	int chars[] = {
		'4',    // at beginning
		'o',    // in middle
		'\0',   // null terminator
		'x',    // not found
		'a',    // multiple matches
		't'     // at end
	};

	int num_inputs = sizeof(inputs) / sizeof(inputs[0]);
	int num_chars = sizeof(chars) / sizeof(chars[0]);

	for (int i = 0; i < num_inputs; i++)
	{
		for (int j = 0; j < num_chars; j++)
		{
			const char *str = inputs[i];
			int c = chars[j];

			char *ft_res = ft_strchr(str, c);
			char *std_res = strchr(str, c);

			if (ft_res != NULL)
				printf("ft_strchr : \"%s\"\n", ft_res);
			else
				printf("ft_strchr : NULL\n");

			if (std_res != NULL)
				printf("strchr    : \"%s\"\n", std_res);
			else
				printf("strchr    : NULL\n");

			if (ft_res == std_res)
			{
				printf("MATCH\n");
			}
			else if (ft_res != NULL && std_res != NULL
					&& strcmp(ft_res, std_res) == 0)
			{
				printf("MATCH\n");
			}
			else
			{
				printf("MISMATCH\n");
			}

			printf("----------------------------------\n");
		}
	}
	return 0;
}*/
