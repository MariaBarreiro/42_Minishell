/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-enca <mda-enca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:12:00 by mda-enca          #+#    #+#             */
/*   Updated: 2025/04/09 09:17:11 by mda-enca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

///ft_isdigit: Check if char digit;
///int c: char to check;
///RETURN: SUCCESS: c:
///RETURN: FAILURE: 0;

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	return (0);
}
/*
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	int tests[] = {'0', '5', '9', 'a', '/', ':', ' ', '\n', -1, 128, 255};
	int i = 0;

	while (i < (int)(sizeof(tests) / sizeof(tests[0])))
	{
		int c = tests[i];

		// Safe comparison
		int ft = ft_isdigit(c);
		int std = isdigit((unsigned char)c);

		printf("  ft_isdigit: %d\n", ft);
		printf("  isdigit   : %d\n", std);

		if (ft == std)
			printf("MATCH\n");
		else
			printf("MISMATCH\n");

		printf("--------------------------\n");
		i++;
	}
	return 0;
}*/
