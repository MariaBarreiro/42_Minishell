/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:02:58 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/08 15:05:06 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///ft_isalpha: Check if char is alphabetic;
///int c: char to check;
///RETURN: SUCCESS: c:
///RETURN: FAILURE: 0;

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1024);
	return (0);
}
/*
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	int tests[] = {'a', 'Z', '5', '@', ' ', '\n', -1, 128};
	int i = 0;

	while (i < (int)(sizeof(tests) / sizeof(tests[0])))
	{
		int c = tests[i];

		// Safely cast for standard isalpha
		int ft = ft_isalpha(c);
		int std = isalpha((unsigned char)c);

		printf("  ft_isalpha: %d\n", ft);
		printf("  isalpha   : %d\n", std);

		if (ft == std)
			printf("MATCH\n");
		else
			printf("MISMATCH\n");

		printf("--------------------------\n");
		i++;
	}
	return 0;
}*/
