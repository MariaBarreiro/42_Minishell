/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 08:53:29 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/18 08:53:31 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///ft_strdup: duplicate a string;
///const char *s: pointer to a string;
///return: success: pointer to the duplicated string;
///return: failure: null;

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	n;
	char	*dup;

	n = 0;
	i = ft_strlen(s);
	dup = (char *)malloc((i + 1) * sizeof(char));
	if (!dup)
		return (0);
	while (n < i)
	{
		dup[n] = s[n];
		n++;
	}
	dup[n] = '\0';
	return (dup);
}
/*
#include <string.h>
#include <stdio.h>

int	main(void)
{
	const char *tests[] = {
		"",
		"42",
		"Hello, world!",
		"   lots   of   space   ",
		"String with symbols! @#$%^&*()",
		"This is a longer string to test duplication.",
	};
	int total = sizeof(tests) / sizeof(tests[0]);
	int i = 0;

	while (i < total)
	{
		const char *src = tests[i];
		char *ft = ft_strdup(src);
		char *og = strdup(src);

		printf("ft_strdup: \"%s\"\n", ft);
		printf("strdup   : \"%s\"\n", og);

		if (ft != NULL && og != NULL && strcmp(ft, og) == 0)
			printf("MATCH\n");
		else
			printf("MISMATCH\n");

		if (ft == og)
			printf("Same pointer\n");
		else
			printf("Different memory locations\n");

		free(ft);
		free(og);

		printf("----------------------------------\n");
		i++;
	}
	return 0;
}*/
