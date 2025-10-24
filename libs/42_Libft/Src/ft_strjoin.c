/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 10:30:25 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/18 09:08:50 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///s1: preffix string;
///s2: suffix string;
///RETURN: SUCCESS: new string;
///RETURN: FAILURE: null;

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		k;
	size_t		l;
	size_t		i;
	size_t		j;
	char		*join;

	if (!s1 || !s2)
		return (0);
	k = ft_strlen(s1);
	l = ft_strlen(s2);
	i = 0;
	j = 0;
	join = (char *)malloc((k + l + 1) * sizeof(char));
	if (!join)
		return (0);
	while (i < k)
		join[j++] = s1[i++];
	i = 0;
	while (i < l)
		join[j++] = s2[i++];
	join[j] = '\0';
	return (join);
}
/*
#include <stdio.h>

int	main(void)
{
	const char *tests1[] = {
		"Hello, ",
		"",
		"42 ",
		NULL,
		"Prefix-"
	};

	const char *tests2[] = {
		"world!",
		"Empty end",
		"",
		"Also NULL",
		NULL
	};

	int total = sizeof(tests1) / sizeof(tests1[0]);
	int i = 0;

	while (i < total)
	{
		const char *s1 = tests1[i];
		const char *s2 = tests2[i];

		if (s1 != NULL)
			printf("s1: \"%s\"\n", s1);
		else
			printf("s1: NULL\n");

		if (s2 != NULL)
			printf("s2: \"%s\"\n", s2);
		else
			printf("s2: NULL\n");

		char *joined = ft_strjoin(s1, s2);

		if (joined != NULL)
		{
			printf("ft_strjoin: \"%s\"\n", joined);
			free(joined);
		}
		else
		{
			printf("ft_strjoin: NULL (allocation failed or input was NULL)\n");
		}

		printf("----------------------------------\n");
		i++;
	}

	return 0;
}*/
